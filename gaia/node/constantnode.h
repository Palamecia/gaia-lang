#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include <node/abstractnode.h>
#include <string>
#include <memory>

class ConstantNode : public AbstractNode {
public:
	ConstantNode();
};

class StringNode : public AbstractNode {
public:
	explicit StringNode(std::string const& token);

	void accept(AbstractNodeVisitor* visitor) override;

	std::string get_literal() const;

private:
	std::string m_literal;
};

class FloatNode : public AbstractNode {
public:
	explicit FloatNode(std::string const& token);

	void accept(AbstractNodeVisitor* visitor) override;

	std::string get_literal() const;

private:
	std::string m_literal;
};

class IntNode : public AbstractNode {
public:
	explicit IntNode(std::string const& token);

	void accept(AbstractNodeVisitor* visitor) override;

	std::string get_literal() const;

private:
	std::string m_literal;
};

class SymbolNode : public AbstractNode {
public:
	explicit SymbolNode(std::string const& token);

	void accept(AbstractNodeVisitor* visitor) override;

	std::string get_symbol() const;

private:
	std::string m_symbol;
};

class ArrayNode : public AbstractNode {
public:
	explicit ArrayNode(AbstractNode* values);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_values() const;

private:
	std::unique_ptr<AbstractNode> m_values;
};

#endif // CONSTANTNODE_H
