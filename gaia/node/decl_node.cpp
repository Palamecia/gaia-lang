#include "decl_node.h"
#include "abstract_node_visitor.h"

#include <functional>
#include <memory>
#include <ranges>

DeclNode::DeclNode(std::unique_ptr<AbstractNode> symbol) :
	m_symbol(std::move(symbol)) {}

auto DeclNode::get_symbol() const -> AbstractNode& {
	return *m_symbol;
}

auto DeclNode::get_flags() const -> DeclNode::Flags {
	return m_flags;
}

void DeclNode::set_flag(Flag flag, bool enabled) {
	m_flags.set(flag, enabled);
}

void TypeNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

SliceTypeNode::SliceTypeNode(std::unique_ptr<AbstractNode> type) :
	DeclNode(nullptr),
	m_type(std::move(type)) {}

void SliceTypeNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

auto SliceTypeNode::get_type() const -> AbstractNode& {
	return *m_type;
}

ArrayTypeNode::ArrayTypeNode(std::unique_ptr<AbstractNode> type, std::unique_ptr<AbstractNode> size) :
	DeclNode(nullptr),
	m_type(std::move(type)),
	m_size(std::move(size)) {}

void ArrayTypeNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

auto ArrayTypeNode::get_type() const -> AbstractNode& {
	return *m_type;
}

auto ArrayTypeNode::get_size() const -> AbstractNode& {
	return *m_size;
}

FnNode::FnNode(std::unique_ptr<AbstractNode> symbol) :
	DeclNode(std::move(symbol)) {}

void FnNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

auto FnNode::get_parameters() const -> AbstractNode& {
	return *m_parameters;
}

void FnNode::set_parameters(std::unique_ptr<AbstractNode> parameters) {
	m_parameters = std::move(parameters);
}

auto FnNode::get_type() const -> AbstractNode& {
	return *m_type;
}

void FnNode::set_type(std::unique_ptr<AbstractNode> type) {
	m_type = std::move(type);
}

auto FnNode::get_body() const -> AbstractNode& {
	return *m_body;
}

void FnNode::set_body(std::unique_ptr<AbstractNode> body) {
	m_body = std::move(body);
}

FnParamNode::FnParamNode(std::unique_ptr<AbstractNode> symbol, std::unique_ptr<AbstractNode> type) :
	DeclNode(std::move(symbol)),
	m_type(std::move(type)) {}

void FnParamNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

auto FnParamNode::get_type() const -> AbstractNode& {
	return *m_type;
}

auto FnParamNode::get_default_value() const -> AbstractNode& {
	return *m_default_value;
}

void FnParamNode::set_default_value(std::unique_ptr<AbstractNode> default_value) {
	m_default_value = std::move(default_value);
}

FnParamListNode::FnParamListNode() = default;

void FnParamListNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

auto FnParamListNode::get_parameters() const -> std::vector<std::reference_wrapper<AbstractNode>> {
	return std::vector(std::from_range, std::views::transform(m_parameters, std::ref<AbstractNode>));
}

void FnParamListNode::append(std::unique_ptr<AbstractNode> parameter) {
	m_parameters.push_back(std::move(parameter));
}

void LetNode::accept(AbstractNodeVisitor& visitor) {
	visitor.visit(*this);
}

auto LetNode::get_type() const -> AbstractNode& {
	return *m_type;
}

void LetNode::set_type(std::unique_ptr<AbstractNode> type) {
	m_type = std::move(type);
}

auto LetNode::get_value() const -> AbstractNode& {
	return *m_value;
}

void LetNode::set_value(std::unique_ptr<AbstractNode> value) {
	m_value = std::move(value);
}
