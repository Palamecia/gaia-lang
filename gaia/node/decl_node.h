#ifndef DECL_NODE_H
#define DECL_NODE_H

#include <functional>
#include <node/abstract_node.h>
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

	using Flags = std::bitset<sizeof(Flag) & CHAR_BIT>;

	explicit DeclNode(std::unique_ptr<AbstractNode> symbol);

	[[nodiscard]] auto get_symbol() const -> AbstractNode&;

	[[nodiscard]] auto get_flags() const -> Flags;
	void set_flag(Flag flag, bool enabled = true);

private:
	std::unique_ptr<AbstractNode> m_symbol;
	Flags m_flags;
};

class TypeNode : public DeclNode {
public:
	using DeclNode::DeclNode;

	void accept(AbstractNodeVisitor& visitor) override;
};

class SliceTypeNode : public DeclNode {
public:
	explicit SliceTypeNode(std::unique_ptr<AbstractNode> type);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_type() const -> AbstractNode&;

private:
	std::unique_ptr<AbstractNode> m_type;
};

class ArrayTypeNode : public DeclNode {
public:
	ArrayTypeNode(std::unique_ptr<AbstractNode> type, std::unique_ptr<AbstractNode> size);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_type() const -> AbstractNode&;

	[[nodiscard]] auto get_size() const -> AbstractNode&;

private:
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_size;
};

class FnNode : public DeclNode {
public:
	explicit FnNode(std::unique_ptr<AbstractNode> symbol = nullptr);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_parameters() const -> AbstractNode&;
	void set_parameters(std::unique_ptr<AbstractNode> parameters);

	[[nodiscard]] auto get_type() const -> AbstractNode&;
	void set_type(std::unique_ptr<AbstractNode> type);

	[[nodiscard]] auto get_body() const -> AbstractNode&;
	void set_body(std::unique_ptr<AbstractNode> body);

private:
	std::unique_ptr<AbstractNode> m_parameters;
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_body;
};

class FnParamNode : public DeclNode {
public:
	FnParamNode(std::unique_ptr<AbstractNode> symbol, std::unique_ptr<AbstractNode> type);

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_type() const -> AbstractNode&;

	[[nodiscard]] auto get_default_value() const -> AbstractNode&;
	void set_default_value(std::unique_ptr<AbstractNode> default_value);

private:
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_default_value;
};

class FnParamListNode : public AbstractNode {
public:
	FnParamListNode();

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_parameters() const -> std::vector<std::reference_wrapper<AbstractNode>>;
	void append(std::unique_ptr<AbstractNode> parameter);

private:
	std::vector<std::unique_ptr<AbstractNode>> m_parameters;
};

class LetNode : public DeclNode {
public:
	using DeclNode::DeclNode;

	void accept(AbstractNodeVisitor& visitor) override;

	[[nodiscard]] auto get_type() const -> AbstractNode&;
	void set_type(std::unique_ptr<AbstractNode> type);

	[[nodiscard]] auto get_value() const -> AbstractNode&;
	void set_value(std::unique_ptr<AbstractNode> value);

private:
	std::unique_ptr<AbstractNode> m_type;
	std::unique_ptr<AbstractNode> m_value;
};

#endif // DECL_NODE_H
