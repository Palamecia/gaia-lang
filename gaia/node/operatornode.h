#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include <node/abstractnode.h>
#include <memory>
#include <vector>

class OperatorNode : public AbstractNode {
public:
	OperatorNode();
};

class CallOperatorNode : public OperatorNode {
public:
	CallOperatorNode(AbstractNode* function, AbstractNode* parameters);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_function() const;
	AbstractNode* get_parameters() const;

private:
	std::unique_ptr<AbstractNode> m_function;
	std::unique_ptr<AbstractNode> m_parameters;
};

class CallParamListNode : public OperatorNode {
public:
	CallParamListNode();
	~CallParamListNode();

	void accept(AbstractNodeVisitor* visitor) override;

	std::vector<AbstractNode*> const& get_parameters() const;
	void append(AbstractNode* parameter);

private:
	std::vector<AbstractNode*> m_parameters;
};

class UnaryOperatorNode : public OperatorNode {
public:
	explicit UnaryOperatorNode(AbstractNode* operand);

	AbstractNode* get_operand() const;

private:
	std::unique_ptr<AbstractNode> m_operand;
};

class PreIncOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class PreDecOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class PostIncOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class PostDecOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class PosOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class NegOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class NotOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class InvOperatorNode : public UnaryOperatorNode {
public:
	using UnaryOperatorNode::UnaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class BinaryOperatorNode : public OperatorNode {
public:
	BinaryOperatorNode(AbstractNode* left, AbstractNode* right);

	AbstractNode* get_left_operand() const;
	AbstractNode* get_right_operand() const;

private:
	std::unique_ptr<AbstractNode> m_left;
	std::unique_ptr<AbstractNode> m_right;
};

class SubscriptOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class ScopeOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class MemberOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class AddOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class SubOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class MulOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class DivOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class ModOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class BitwiseAndOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class BitwiseXorOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class BitwiseOrOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class AndOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class OrOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class EqOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class NeOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class GtOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class GeOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class LtOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class LeOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class ShiftLeftOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class ShiftRightOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class InclusiveRangeOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

class ExclusiveRangeOperatorNode : public BinaryOperatorNode {
public:
	using BinaryOperatorNode::BinaryOperatorNode;

	void accept(AbstractNodeVisitor* visitor) override;
};

#endif // OPERATORNODE_H
