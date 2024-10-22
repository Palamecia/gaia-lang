#ifndef ABSTRACT_NODE_H
#define ABSTRACT_NODE_H

class AbstractNodeVisitor;

class AbstractNode {
public:
	AbstractNode();
	AbstractNode(const AbstractNode&) = delete;
	AbstractNode(AbstractNode&&) = delete;
	virtual ~AbstractNode();

	auto operator=(const AbstractNode&) -> AbstractNode& = delete;
	auto operator=(AbstractNode&&) -> AbstractNode& = delete;

	virtual void accept(AbstractNodeVisitor& visitor) = 0;
};

#endif // ABSTRACT_NODE_H
