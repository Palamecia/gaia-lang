#ifndef DECLNODE_H
#define DECLNODE_H

#include <node/abstractnode.h>
#include <memory>
#include <vector>
#include <bitset>

class DeclNode : public AbstractNode {
public:
	enum Flag : std::uint8_t {
		NO_FLAG = 0,
		PUB_FLAG = 1 << 0,
		MUT_FLAG = 1 << 1,
		OPT_FLAG = 1 << 2,
		PTR_FLAG = 1 << 3,
		MOVE_FLAG = 1 << 4,
		COPY_FLAG = 1 << 5,
	};
	using Flags = std::bitset<sizeof(Flag) * CHAR_BIT>;

	explicit DeclNode(AbstractNode* symbol);

	AbstractNode* get_symbol() const;

	Flags get_flags() const;
	void set_flag(Flag flag, bool enabled = true);

private:
	std::unique_ptr<AbstractNode> m_symbol;
	Flags m_flags;
};

class TypeNode : public DeclNode {
public:
	using DeclNode::DeclNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class SliceTypeNode : public DeclNode {
public:
	explicit SliceTypeNode(AbstractNode* type);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_type() const;

private:
	std::unique_ptr<AbstractNode> m_type;
};

class ArrayTypeNode : public DeclNode {
public:
	ArrayTypeNode(AbstractNode* type, AbstractNode* size);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_type() const;

	AbstractNode* get_size() const;

private:
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_size;
};

class FnNode : public DeclNode {
public:
	explicit FnNode(AbstractNode* symbol = nullptr);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_parameters() const;
	void set_parameters(AbstractNode* parameters);

	AbstractNode* get_type() const;
	void set_type(AbstractNode* type);

	AbstractNode* get_body() const;
	void set_body(AbstractNode* body);

private:
	std::unique_ptr<AbstractNode> m_parameters;
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_body;
};

class FnParamNode : public DeclNode {
public:
	FnParamNode(AbstractNode* symbol, AbstractNode* type);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_type() const;

	AbstractNode* get_default_value() const;
	void set_default_value(AbstractNode* default_value);

private:
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_default_value;
};

class FnParamListNode : public AbstractNode {
public:
	FnParamListNode();
	~FnParamListNode();

	void accept(AbstractNodeVisitor* visitor) override;

	std::vector<AbstractNode*> const& get_parameters() const;
	void append(AbstractNode* parameter);

private:
	std::vector<AbstractNode*> m_parameters;
};

class LetNode : public DeclNode {
public:
	using DeclNode::DeclNode;

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_type() const;
	void set_type(AbstractNode* type);

	AbstractNode* get_value() const;
	void set_value(AbstractNode* value);

private:
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_value;
};

#endif // DECLNODE_H
