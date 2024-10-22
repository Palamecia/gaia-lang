#include "buildnodevisitor.h"
#include "node/constantnode.h"
#include "node/declnode.h"
#include "node/flownode.h"
#include "node/operatornode.h"

BuildNodeVisitor::BuildNodeVisitor() :
	m_builder(m_context) {}

void BuildNodeVisitor::visit(StmtListNode* node) {
	switch (m_state) {
	case BUILD_GLOBAL_SCOPE:
		for (AbstractNode* child : node->get_nodes()) {
			child->accept(this);
		}
		break;
	case BUILD_FUNCTION_BODY:
		break;
	default:
		break;
	}
}

void BuildNodeVisitor::visit(IfElseNode* node) {

}

void BuildNodeVisitor::visit(SwitchNode* node) {

}

void BuildNodeVisitor::visit(CaseListNode* node) {

}

void BuildNodeVisitor::visit(CaseNode* node) {

}

void BuildNodeVisitor::visit(DefaultNode* node) {

}

void BuildNodeVisitor::visit(WhileNode* node) {

}

void BuildNodeVisitor::visit(ForRangeNode* node) {

}

void BuildNodeVisitor::visit(ForIterNode* node) {

}

void BuildNodeVisitor::visit(ReturnNode* node) {

}

void BuildNodeVisitor::visit(BreakNode* node) {

}

void BuildNodeVisitor::visit(ContinueNode* node) {

}

void BuildNodeVisitor::visit(TypeNode* node) {

}

void BuildNodeVisitor::visit(SliceTypeNode* node) {

}

void BuildNodeVisitor::visit(ArrayTypeNode* node) {

}

void BuildNodeVisitor::visit(FnNode* node) {
	switch (m_state) {
	case BUILD_GLOBAL_SCOPE:
		m_state = BUILD_FUNCTION_DEFINITION;
		visit_next(node->get_symbol());
		m_state = BUILD_FUNCTION_PARAMETERS;
		visit_next(node->get_parameters());
		m_state = BUILD_FUNCTION_BODY;
		visit_next(node->get_body());
		m_state = BUILD_GLOBAL_SCOPE;
		break;
	default:
		break;
	}
}

void BuildNodeVisitor::visit(FnParamNode* node) {

}

void BuildNodeVisitor::visit(FnParamListNode* node) {

}

void BuildNodeVisitor::visit(LetNode* node) {

}

void BuildNodeVisitor::visit(CallOperatorNode* node) {

}

void BuildNodeVisitor::visit(CallParamListNode* node) {

}

void BuildNodeVisitor::visit(PreIncOperatorNode* node) {

}

void BuildNodeVisitor::visit(PreDecOperatorNode* node) {

}

void BuildNodeVisitor::visit(PostIncOperatorNode* node) {

}

void BuildNodeVisitor::visit(PostDecOperatorNode* node) {

}

void BuildNodeVisitor::visit(SubscriptOperatorNode* node) {

}

void BuildNodeVisitor::visit(MemberOperatorNode* node) {

}

void BuildNodeVisitor::visit(AddOperatorNode* node) {

}

void BuildNodeVisitor::visit(SubOperatorNode* node) {

}

void BuildNodeVisitor::visit(MulOperatorNode* node) {

}

void BuildNodeVisitor::visit(DivOperatorNode* node) {

}

void BuildNodeVisitor::visit(ModOperatorNode* node) {

}

void BuildNodeVisitor::visit(BitwiseAndOperatorNode* node) {

}

void BuildNodeVisitor::visit(BitwiseOrOperatorNode* node) {

}

void BuildNodeVisitor::visit(AndOperatorNode* node) {

}

void BuildNodeVisitor::visit(OrOperatorNode* node) {

}

void BuildNodeVisitor::visit(EqOperatorNode* node) {

}

void BuildNodeVisitor::visit(NeOperatorNode* node) {

}

void BuildNodeVisitor::visit(LtOperatorNode* node) {

}

void BuildNodeVisitor::visit(LeOperatorNode* node) {

}

void BuildNodeVisitor::visit(GtOperatorNode* node) {

}

void BuildNodeVisitor::visit(GeOperatorNode* node) {

}

void BuildNodeVisitor::visit(InclusiveRangeOperatorNode* node) {

}

void BuildNodeVisitor::visit(ExclusiveRangeOperatorNode* node) {

}

void BuildNodeVisitor::visit(StringNode* node) {

}

void BuildNodeVisitor::visit(FloatNode* node) {

}

void BuildNodeVisitor::visit(IntNode* node) {

}

void BuildNodeVisitor::visit(SymbolNode* node) {
	switch (m_state) {
	case BUILD_FUNCTION_DEFINITION:
		break;
	case BUILD_FUNCTION_PARAMETERS:
		break;
	default:
		break;
	}
}

void BuildNodeVisitor::visit(ArrayNode* node) {

}

bool BuildNodeVisitor::visit_next(AbstractNode* node) {
	if (!node) {
		return false;
	}
	node->accept(this);
	return true;
}
