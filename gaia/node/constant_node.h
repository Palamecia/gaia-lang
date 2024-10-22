#ifndef CONSTANT_NODE_H
#define CONSTANT_NODE_H

#include <node/abstract_node.h>
#include <string>
#include <memory>

class ConstantNode : public AbstractNode {
public:
	ConstantNode();
};

class StringNode : public AbstractNode {
public:
	explicit StringNode(std::string const& token);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_literal() const -> std::string;

private:
	std::string m_literal;
};

class FloatNode : public AbstractNode {
public:
	explicit FloatNode(std::string const& token);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_literal() const -> std::string;

private:
	std::string m_literal;
};

class IntNode : public AbstractNode {
public:
	explicit IntNode(std::string const& token);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_literal() const -> std::string;

private:
	std::string m_literal;
};

class SymbolNode : public AbstractNode {
public:
	explicit SymbolNode(std::string const& token);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_literal() const -> std::string;

private:
	std::string m_symbol;
};

class ArrayNode : public AbstractNode {
public:
	explicit ArrayNode(AbstractNode& values);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_values() const -> AbstractNode*;

private:
	std::unique_ptr<AbstractNode> m_values;
};

#endif // CONSTANT_NODE_H
