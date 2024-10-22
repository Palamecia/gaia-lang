#include "testnodevisitor.h"
#include "node/declnode.h"
#include "node/flownode.h"
#include "node/constantnode.h"
#include "node/operatornode.h"
#include <cstdio>
#include <string>

static void visit_node(AbstractNode* node, AbstractNodeVisitor* visitor) {
	if (node) {
		node->accept(visitor);
	}
}

TestNodeVisitor::TestNodeVisitor() {}

void TestNodeVisitor::visit(StmtListNode* node) {
	std::fprintf(stdout, "%sSTMT:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	for (AbstractNode* child : node->get_nodes()) {
		child->accept(this);
	}
	--m_depth;
}

void TestNodeVisitor::visit(IfElseNode* node) {
	std::fprintf(stdout, "%sIF:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_condition()->accept(this);
	visit_node(node->get_true_branch(), this);
	visit_node(node->get_false_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(SwitchNode* node) {
	std::fprintf(stdout, "%sSWITCH:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_condition()->accept(this);
	visit_node(node->get_label(), this);
	visit_node(node->get_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(CaseListNode* node) {
	std::fprintf(stdout, "%sCASES:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	for (AbstractNode* child : node->get_cases()) {
		child->accept(this);
	}
	--m_depth;
}

void TestNodeVisitor::visit(CaseNode* node) {
	std::fprintf(stdout, "%sCASE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_condition()->accept(this);
	visit_node(node->get_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(DefaultNode* node) {
	std::fprintf(stdout, "%sDEFAULT:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	visit_node(node->get_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(WhileNode* node) {
	std::fprintf(stdout, "%sWHILE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_condition()->accept(this);
	visit_node(node->get_label(), this);
	visit_node(node->get_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(ForRangeNode* node) {
	std::fprintf(stdout, "%sFOR:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_symbol()->accept(this);
	node->get_expr()->accept(this);
	visit_node(node->get_label(), this);
	visit_node(node->get_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(ForIterNode* node) {
	std::fprintf(stdout, "%sFOR:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	visit_node(node->get_init(), this);
	visit_node(node->get_condition(), this);
	visit_node(node->get_next(), this);
	visit_node(node->get_label(), this);
	visit_node(node->get_branch(), this);
	--m_depth;
}

void TestNodeVisitor::visit(ReturnNode* node) {
	std::fprintf(stdout, "%sRETURN:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	visit_node(node->get_expr(), this);
	--m_depth;
}

void TestNodeVisitor::visit(BreakNode* node) {
	std::fprintf(stdout, "%sBREAK:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	visit_node(node->get_expr(), this);
	--m_depth;
}

void TestNodeVisitor::visit(ContinueNode* node) {
	std::fprintf(stdout, "%sCONTINUE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	visit_node(node->get_expr(), this);
	--m_depth;
}

void TestNodeVisitor::visit(TypeNode* node) {
	std::fprintf(stdout, "%sTYPE: %s\n", std::string(m_depth, '>').c_str(), node->get_flags().to_string().c_str());
	++m_depth;
	node->get_symbol()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(SliceTypeNode* node) {
	std::fprintf(stdout, "%sSLICE: %s\n", std::string(m_depth, '>').c_str(), node->get_flags().to_string().c_str());
	++m_depth;
	visit_node(node->get_symbol(), this);
	node->get_type()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(ArrayTypeNode* node) {
	std::fprintf(stdout, "%sARRAY: %s\n", std::string(m_depth, '>').c_str(), node->get_flags().to_string().c_str());
	++m_depth;
	visit_node(node->get_symbol(), this);
	node->get_type()->accept(this);
	node->get_size()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(FnNode* node) {
	std::fprintf(stdout, "%sFN: %s\n", std::string(m_depth, '>').c_str(), node->get_flags().to_string().c_str());
	++m_depth;
	node->get_symbol()->accept(this);
	node->get_parameters()->accept(this);
	visit_node(node->get_type(), this);
	node->get_body()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(FnParamNode* node) {
	std::fprintf(stdout, "%sPARAM: %s\n", std::string(m_depth, '>').c_str(), node->get_flags().to_string().c_str());
	++m_depth;
	node->get_symbol()->accept(this);
	node->get_type()->accept(this);
	visit_node(node->get_default_value(), this);
	--m_depth;
}

void TestNodeVisitor::visit(FnParamListNode* node) {
	std::fprintf(stdout, "%sPARAMS:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	for (AbstractNode* child : node->get_parameters()) {
		child->accept(this);
	}
	--m_depth;
}

void TestNodeVisitor::visit(LetNode* node) {
	std::fprintf(stdout, "%sLET: %s\n", std::string(m_depth, '>').c_str(), node->get_flags().to_string().c_str());
	++m_depth;
	node->get_symbol()->accept(this);
	visit_node(node->get_type(), this);
	node->get_value()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(class CallOperatorNode* node) {
	std::fprintf(stdout, "%sCALL:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_function()->accept(this);
	node->get_parameters()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(class CallParamListNode* node) {
	std::fprintf(stdout, "%sPARAMS:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	for (AbstractNode* child : node->get_parameters()) {
		child->accept(this);
	}
	--m_depth;
}

void TestNodeVisitor::visit(PreIncOperatorNode* node) {
	std::fprintf(stdout, "%sPRE INC:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(PreDecOperatorNode* node) {
	std::fprintf(stdout, "%sPRE DEC:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(PostIncOperatorNode* node) {
	std::fprintf(stdout, "%sPOST INC:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(PostDecOperatorNode* node) {
	std::fprintf(stdout, "%sPOST DEC:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(SubscriptOperatorNode* node) {
	std::fprintf(stdout, "%sSUBSCRIPT:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(MemberOperatorNode* node) {
	std::fprintf(stdout, "%sMEMBER:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(AddOperatorNode* node) {
	std::fprintf(stdout, "%sADD:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(SubOperatorNode* node) {
	std::fprintf(stdout, "%sSUB:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(MulOperatorNode* node) {
	std::fprintf(stdout, "%sMUL:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(DivOperatorNode* node) {
	std::fprintf(stdout, "%sDIV:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(ModOperatorNode* node) {
	std::fprintf(stdout, "%sMOD:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(BitwiseAndOperatorNode* node) {
	std::fprintf(stdout, "%sBITWISE AND:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(BitwiseOrOperatorNode* node) {
	std::fprintf(stdout, "%sBITWISE OR:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(AndOperatorNode* node) {
	std::fprintf(stdout, "%sAND:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(OrOperatorNode* node) {
	std::fprintf(stdout, "%sOR:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(EqOperatorNode* node) {
	std::fprintf(stdout, "%sEQ:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(NeOperatorNode* node) {
	std::fprintf(stdout, "%sNE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(LtOperatorNode* node) {
	std::fprintf(stdout, "%sLT:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(LeOperatorNode* node) {
	std::fprintf(stdout, "%sLE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(GtOperatorNode* node) {
	std::fprintf(stdout, "%sGT:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(GeOperatorNode* node) {
	std::fprintf(stdout, "%sGE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(InclusiveRangeOperatorNode* node) {
	std::fprintf(stdout, "%sINCLUSIVE RANGE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(ExclusiveRangeOperatorNode* node) {
	std::fprintf(stdout, "%sEXCLUSIVE RANGE:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_left_operand()->accept(this);
	node->get_right_operand()->accept(this);
	--m_depth;
}

void TestNodeVisitor::visit(StringNode* node) {
	std::fprintf(stdout, "%sSTRING: %s\n", std::string(m_depth, '>').c_str(), node->get_literal().c_str());
}

void TestNodeVisitor::visit(FloatNode* node) {
	std::fprintf(stdout, "%sFLOAT: %s\n", std::string(m_depth, '>').c_str(), node->get_literal().c_str());
}

void TestNodeVisitor::visit(IntNode* node) {
	std::fprintf(stdout, "%sINT: %s\n", std::string(m_depth, '>').c_str(), node->get_literal().c_str());
}

void TestNodeVisitor::visit(SymbolNode* node) {
	std::fprintf(stdout, "%sSYMBOL: %s\n", std::string(m_depth, '>').c_str(), node->get_symbol().c_str());
}

void TestNodeVisitor::visit(ArrayNode* node) {
	std::fprintf(stdout, "%sARRAY:\n", std::string(m_depth, '>').c_str());
	++m_depth;
	node->get_values()->accept(this);
	--m_depth;
}
