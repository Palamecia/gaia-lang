#include "flownode.h"
#include "abstractnodevisitor.h"

#include <algorithm>

FlowNode::FlowNode() {}

StmtListNode::StmtListNode() {}

StmtListNode::~StmtListNode() {
	std::ranges::for_each(m_nodes, std::default_delete<AbstractNode>());
}

void StmtListNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::vector<AbstractNode*> const& StmtListNode::get_nodes() const {
	return m_nodes;
}

void StmtListNode::append(AbstractNode* node) {
	m_nodes.push_back(node);
}

IfElseNode::IfElseNode(AbstractNode* condition) :
	m_condition(condition) {

}

void IfElseNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* IfElseNode::get_condition() const {
	return m_condition.get();
}

AbstractNode* IfElseNode::get_true_branch() const {
	return m_true_branch.get();
}

void IfElseNode::set_true_branch(AbstractNode* branch) {
	m_true_branch.reset(branch);
}

AbstractNode* IfElseNode::get_false_branch() const {
	return m_false_branch.get();
}

void IfElseNode::set_false_branch(AbstractNode* branch) {
	m_false_branch.reset(branch);
}

SwitchNode::SwitchNode(AbstractNode* condition) :
	m_condition(condition) {}

void SwitchNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* SwitchNode::get_condition() const {
	return m_condition.get();
}

AbstractNode* SwitchNode::get_label() const {
	return m_label.get();
}

void SwitchNode::set_label(AbstractNode* label) {
	m_label.reset(label);
}

AbstractNode* SwitchNode::get_branch() const {
	return m_branch.get();
}

void SwitchNode::set_branch(AbstractNode* branch) {
	m_branch.reset(branch);
}

CaseListNode::CaseListNode() {}

CaseListNode::~CaseListNode() {
	std::ranges::for_each(m_cases, std::default_delete<AbstractNode>());
}

void CaseListNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::vector<AbstractNode*> const& CaseListNode::get_cases() const {
	return m_cases;
}

void CaseListNode::append(AbstractNode* node) {
	m_cases.push_back(node);
}

CaseNode::CaseNode(AbstractNode* condition) :
	m_condition(condition) {}

void CaseNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* CaseNode::get_condition() const {
	return m_condition.get();
}

AbstractNode* CaseNode::get_branch() const {
	return m_branch.get();
}

void CaseNode::set_branch(AbstractNode* branch) {
	m_branch.reset(branch);
}

DefaultNode::DefaultNode() {}

void DefaultNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* DefaultNode::get_branch() const {
	return m_branch.get();
}

void DefaultNode::set_branch(AbstractNode* branch) {
	m_branch.reset(branch);
}

WhileNode::WhileNode(AbstractNode* condition) :
	m_condition(condition) {}

void WhileNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* WhileNode::get_condition() const {
	return m_condition.get();
}

AbstractNode* WhileNode::get_label() const {
	return m_label.get();
}

void WhileNode::set_label(AbstractNode* label) {
	m_label.reset(label);
}

AbstractNode* WhileNode::get_branch() const {
	return m_branch.get();
}

void WhileNode::set_branch(AbstractNode* branch) {
	m_branch.reset(branch);
}

ForRangeNode::ForRangeNode(AbstractNode* symbol, AbstractNode* expr) :
	m_symbol(symbol), m_expr(expr) {}

void ForRangeNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* ForRangeNode::get_symbol() const {
	return m_symbol.get();
}

AbstractNode* ForRangeNode::get_expr() const {
	return m_expr.get();
}

AbstractNode* ForRangeNode::get_label() const {
	return m_label.get();
}

void ForRangeNode::set_label(AbstractNode* label) {
	m_label.reset(label);
}

AbstractNode* ForRangeNode::get_branch() const {
	return m_branch.get();
}

void ForRangeNode::set_branch(AbstractNode* branch) {
	m_branch.reset(branch);
}

ForIterNode::ForIterNode(AbstractNode* init, AbstractNode* condition, AbstractNode* next) :
	m_init(init), m_condition(condition), m_next(next) {}

void ForIterNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* ForIterNode::get_init() const {
	return m_init.get();
}

AbstractNode* ForIterNode::get_condition() const {
	return m_condition.get();
}

AbstractNode* ForIterNode::get_next() const {
	return m_next.get();
}

AbstractNode* ForIterNode::get_label() const {
	return m_label.get();
}

void ForIterNode::set_label(AbstractNode* label) {
	m_label.reset(label);
}

AbstractNode* ForIterNode::get_branch() const {
	return m_branch.get();
}

void ForIterNode::set_branch(AbstractNode* branch) {
	m_branch.reset(branch);
}

ReturnNode::ReturnNode(AbstractNode* expr) :
	m_expr(expr) {}

void ReturnNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* ReturnNode::get_expr() const {
	return m_expr.get();
}

BreakNode::BreakNode(AbstractNode* expr) :
	m_expr(expr) {}

void BreakNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* BreakNode::get_expr() const {
	return m_expr.get();
}

ContinueNode::ContinueNode(AbstractNode* expr) :
	m_expr(expr) {}

void ContinueNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* ContinueNode::get_expr() const {
	return m_expr.get();
}
