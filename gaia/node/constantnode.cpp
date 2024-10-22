#include "constantnode.h"
#include "abstractnodevisitor.h"

ConstantNode::ConstantNode() {}

StringNode::StringNode(std::string const& token) :
	m_literal(token) {}

void StringNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::string StringNode::get_literal() const {
	return m_literal;
}

FloatNode::FloatNode(std::string const& token) :
	m_literal(token) {}

void FloatNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::string FloatNode::get_literal() const {
	return m_literal;
}

IntNode::IntNode(std::string const& token) :
	m_literal(token) {}

void IntNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::string IntNode::get_literal() const {
	return m_literal;
}

SymbolNode::SymbolNode(std::string const& token) :
	m_symbol(token) {}

void SymbolNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

std::string SymbolNode::get_symbol() const {
	return m_symbol;
}

ArrayNode::ArrayNode(AbstractNode* values) :
	m_values(values) {}

void ArrayNode::accept(AbstractNodeVisitor* visitor) {
	visitor->visit(this);
}

AbstractNode* ArrayNode::get_values() const {
	return m_values.get();
}
