#include "declnode.h"
#include "abstractnodevisitor.h"

#include <algorithm>

DeclNode::DeclNode(AbstractNode* symbol) :
	m_symbol(symbol) {}

AbstractNode* DeclNode::get_symbol() const {
	return m_symbol.get();
}

DeclNode::Flags DeclNode::get_flags() const {
	return m_flags;
}

void DeclNode::set_flag(Flag flag, bool enabled) {
	m_flags.set(flag, enabled);
}

void TypeNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

SliceTypeNode::SliceTypeNode(AbstractNode* type) :
	DeclNode(nullptr), m_type(type) {

}

void SliceTypeNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* SliceTypeNode::get_type() const {
	return m_type.get();
}

ArrayTypeNode::ArrayTypeNode(AbstractNode* type, AbstractNode* size) :
	DeclNode(nullptr), m_type(type), m_size(size) {

}

void ArrayTypeNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* ArrayTypeNode::get_type() const {
	return m_type.get();
}

AbstractNode* ArrayTypeNode::get_size() const {
	return m_size.get();
}

FnNode::FnNode(AbstractNode* symbol) :
	DeclNode(symbol) {}

void FnNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* FnNode::get_parameters() const {
	return m_parameters.get();
}

void FnNode::set_parameters(AbstractNode* parameters) {
	m_parameters.reset(parameters);
}

AbstractNode* FnNode::get_type() const {
	return m_type.get();
}

void FnNode::set_type(AbstractNode* type) {
	m_type.reset(type);
}

AbstractNode* FnNode::get_body() const {
	return m_body.get();
}

void FnNode::set_body(AbstractNode* body) {
	m_body.reset(body);
}

FnParamNode::FnParamNode(AbstractNode* symbol, AbstractNode* type) :
	DeclNode(symbol), m_type(type) {}

void FnParamNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* FnParamNode::get_type() const {
	return m_type.get();
}

AbstractNode* FnParamNode::get_default_value() const {
	return m_default_value.get();
}

void FnParamNode::set_default_value(AbstractNode* default_value) {
	m_default_value.reset(default_value);
}

FnParamListNode::FnParamListNode() {}

FnParamListNode::~FnParamListNode() {
	std::ranges::for_each(m_parameters, std::default_delete<AbstractNode>());
}

void FnParamListNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::vector<AbstractNode*> const& FnParamListNode::get_parameters() const {
	return m_parameters;
}

void FnParamListNode::append(AbstractNode* parameter) {
	m_parameters.push_back(parameter);
}

void LetNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* LetNode::get_type() const {
	return m_type.get();
}

void LetNode::set_type(AbstractNode* type) {
	m_type.reset(type);
}

AbstractNode* LetNode::get_value() const {
	return m_value.get();
}

void LetNode::set_value(AbstractNode* value) {
	m_value.reset(value);
}
