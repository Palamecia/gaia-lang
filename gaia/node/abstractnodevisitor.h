#ifndef ABSTRACTNODEVISITOR_H
#define ABSTRACTNODEVISITOR_H

class AbstractNodeVisitor {
public:
	AbstractNodeVisitor();

	virtual void visit(class StmtListNode* node);
	virtual void visit(class IfElseNode* node);
	virtual void visit(class SwitchNode* node);
	virtual void visit(class CaseListNode* node);
	virtual void visit(class CaseNode* node);
	virtual void visit(class DefaultNode* node);
	virtual void visit(class WhileNode* node);
	virtual void visit(class ForRangeNode* node);
	virtual void visit(class ForIterNode* node);
	virtual void visit(class ReturnNode* node);
	virtual void visit(class BreakNode* node);
	virtual void visit(class ContinueNode* node);

	virtual void visit(class TypeNode* node);
	virtual void visit(class SliceTypeNode* node);
	virtual void visit(class ArrayTypeNode* node);
	virtual void visit(class FnNode* node);
	virtual void visit(class FnParamNode* node);
	virtual void visit(class FnParamListNode* node);
	virtual void visit(class LetNode* node);

	virtual void visit(class CallOperatorNode* node);
	virtual void visit(class CallParamListNode* node);
	virtual void visit(class PreIncOperatorNode* node);
	virtual void visit(class PreDecOperatorNode* node);
	virtual void visit(class PostIncOperatorNode* node);
	virtual void visit(class PostDecOperatorNode* node);
	virtual void visit(class PosOperatorNode* node);
	virtual void visit(class NegOperatorNode* node);
	virtual void visit(class NotOperatorNode* node);
	virtual void visit(class InvOperatorNode* node);
	virtual void visit(class SubscriptOperatorNode* node);
	virtual void visit(class ScopeOperatorNode* node);
	virtual void visit(class MemberOperatorNode* node);
	virtual void visit(class AddOperatorNode* node);
	virtual void visit(class SubOperatorNode* node);
	virtual void visit(class MulOperatorNode* node);
	virtual void visit(class DivOperatorNode* node);
	virtual void visit(class ModOperatorNode* node);
	virtual void visit(class BitwiseAndOperatorNode* node);
	virtual void visit(class BitwiseXorOperatorNode* node);
	virtual void visit(class BitwiseOrOperatorNode* node);
	virtual void visit(class AndOperatorNode* node);
	virtual void visit(class OrOperatorNode* node);
	virtual void visit(class EqOperatorNode* node);
	virtual void visit(class NeOperatorNode* node);
	virtual void visit(class LtOperatorNode* node);
	virtual void visit(class LeOperatorNode* node);
	virtual void visit(class GtOperatorNode* node);
	virtual void visit(class GeOperatorNode* node);
	virtual void visit(class ShiftLeftOperatorNode* node);
	virtual void visit(class ShiftRightOperatorNode* node);
	virtual void visit(class InclusiveRangeOperatorNode* node);
	virtual void visit(class ExclusiveRangeOperatorNode* node);

	virtual void visit(class StringNode* node);
	virtual void visit(class FloatNode* node);
	virtual void visit(class IntNode* node);
	virtual void visit(class SymbolNode* node);
	virtual void visit(class ArrayNode* node);
};

#endif // ABSTRACTNODEVISITOR_H
