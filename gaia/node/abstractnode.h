#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

class AbstractNodeVisitor;

class AbstractNode {
public:
	AbstractNode();
	virtual ~AbstractNode();

	virtual void accept(AbstractNodeVisitor* visitor) = 0;
};

#endif // ABSTRACTNODE_H
