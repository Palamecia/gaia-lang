#include "operatornode.h"
#include "abstractnodevisitor.h"

#include <algorithm>

OperatorNode::OperatorNode() {}

CallOperatorNode::CallOperatorNode(AbstractNode* function, AbstractNode* parameters) :
	m_function(function), m_parameters(parameters) {}

void CallOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* CallOperatorNode::get_function() const {
	return m_function.get();
}

AbstractNode* CallOperatorNode::get_parameters() const {
	return m_parameters.get();
}

CallParamListNode::CallParamListNode() {}

CallParamListNode::~CallParamListNode() {
	std::ranges::for_each(m_parameters, std::default_delete<AbstractNode>());
}

void CallParamListNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::vector<AbstractNode*> const& CallParamListNode::get_parameters() const {
	return m_parameters;
}

void CallParamListNode::append(AbstractNode* parameter) {
	m_parameters.push_back(parameter);
}

UnaryOperatorNode::UnaryOperatorNode(AbstractNode* operand) :
	m_operand(operand) {}

AbstractNode* UnaryOperatorNode::get_operand() const {
	return m_operand.get();
}

void PreIncOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void PreDecOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void PostIncOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void PostDecOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void PosOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void NegOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void NotOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void InvOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

BinaryOperatorNode::BinaryOperatorNode(AbstractNode* left, AbstractNode* right) :
	m_left(left), m_right(right) {}

AbstractNode* BinaryOperatorNode::get_left_operand() const {
	return m_left.get();
}

AbstractNode* BinaryOperatorNode::get_right_operand() const {
	return m_right.get();
}

void SubscriptOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void ScopeOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void MemberOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void AddOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void SubOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void MulOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void DivOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void ModOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void BitwiseAndOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void BitwiseXorOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void BitwiseOrOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void AndOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void OrOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void EqOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void NeOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void LtOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void LeOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void GtOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void GeOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void ShiftLeftOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void ShiftRightOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void InclusiveRangeOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

void ExclusiveRangeOperatorNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}
