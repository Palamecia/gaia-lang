#ifndef FLOWNODE_H
#define FLOWNODE_H

#include <node/abstractnode.h>
#include <memory>
#include <vector>

class FlowNode : public AbstractNode {
public:
	FlowNode();
};

class StmtListNode : public FlowNode {
public:
	StmtListNode();
	~StmtListNode();

	void accept(AbstractNodeVisitor* visitor) override;

	std::vector<AbstractNode*> const& get_nodes() const;
	void append(AbstractNode* node);

private:
	std::vector<AbstractNode*> m_nodes;
};

class IfElseNode : public FlowNode {
public:
	explicit IfElseNode(AbstractNode* condition);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_condition() const;

	AbstractNode* get_true_branch() const;
	void set_true_branch(AbstractNode* branch);

	AbstractNode* get_false_branch() const;
	void set_false_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_condition;
	std::unique_ptr<AbstractNode> m_true_branch;
	std::unique_ptr<AbstractNode> m_false_branch;
};

class SwitchNode : public FlowNode {
public:
	explicit SwitchNode(AbstractNode* condition);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_condition() const;

	AbstractNode* get_label() const;
	void set_label(AbstractNode* label);

	AbstractNode* get_branch() const;
	void set_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_condition;
	std::unique_ptr<AbstractNode> m_label;
	std::unique_ptr<AbstractNode> m_branch;
};

class CaseListNode : public FlowNode {
public:
	CaseListNode();
	~CaseListNode();

	void accept(AbstractNodeVisitor* visitor) override;

	std::vector<AbstractNode*> const& get_cases() const;
	void append(AbstractNode* node);

private:
	std::vector<AbstractNode*> m_cases;
};

class CaseNode : public FlowNode {
public:
	explicit CaseNode(AbstractNode* condition);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_condition() const;

	AbstractNode* get_branch() const;
	void set_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_condition;
	std::unique_ptr<AbstractNode> m_branch;
};

class DefaultNode : public FlowNode {
public:
	DefaultNode();

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_branch() const;
	void set_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_branch;
};

class WhileNode : public FlowNode {
public:
	explicit WhileNode(AbstractNode* condition);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_condition() const;

	AbstractNode* get_label() const;
	void set_label(AbstractNode* label);

	AbstractNode* get_branch() const;
	void set_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_condition;
	std::unique_ptr<AbstractNode> m_label;
	std::unique_ptr<AbstractNode> m_branch;
};

class ForRangeNode : public FlowNode {
public:
	ForRangeNode(AbstractNode* symbol, AbstractNode* expr);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_symbol() const;

	AbstractNode* get_expr() const;

	AbstractNode* get_label() const;
	void set_label(AbstractNode* label);

	AbstractNode* get_branch() const;
	void set_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_symbol;
	std::unique_ptr<AbstractNode> m_expr;
	std::unique_ptr<AbstractNode> m_label;
	std::unique_ptr<AbstractNode> m_branch;
};

class ForIterNode : public FlowNode {
public:
	ForIterNode(AbstractNode* init, AbstractNode* condition, AbstractNode* next);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_init() const;

	AbstractNode* get_condition() const;

	AbstractNode* get_next() const;

	AbstractNode* get_label() const;
	void set_label(AbstractNode* label);

	AbstractNode* get_branch() const;
	void set_branch(AbstractNode* branch);

private:
	std::unique_ptr<AbstractNode> m_init;
	std::unique_ptr<AbstractNode> m_condition;
	std::unique_ptr<AbstractNode> m_next;
	std::unique_ptr<AbstractNode> m_label;
	std::unique_ptr<AbstractNode> m_branch;
};

class ReturnNode : public FlowNode {
public:
	explicit ReturnNode(AbstractNode* expr = nullptr);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_expr() const;

private:
	std::unique_ptr<AbstractNode> m_expr;
};

class BreakNode : public FlowNode {
public:
	explicit BreakNode(AbstractNode* expr = nullptr);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_expr() const;

private:
	std::unique_ptr<AbstractNode> m_expr;
};

class ContinueNode : public FlowNode {
public:
	explicit ContinueNode(AbstractNode* expr = nullptr);

	void accept(AbstractNodeVisitor* visitor) override;

	AbstractNode* get_expr() const;

private:
	std::unique_ptr<AbstractNode> m_expr;
};

#endif // FLOWNODE_H
