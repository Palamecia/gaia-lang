#ifndef BUILDNODEVISITOR_H
#define BUILDNODEVISITOR_H

#include <node/abstractnodevisitor.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

class BuildNodeVisitor : public AbstractNodeVisitor {
public:
	BuildNodeVisitor();

	void visit(class StmtListNode* node) override;
	void visit(class IfElseNode* node) override;
	void visit(class SwitchNode* node) override;
	void visit(class CaseListNode* node) override;
	void visit(class CaseNode* node) override;
	void visit(class DefaultNode* node) override;
	void visit(class WhileNode* node) override;
	void visit(class ForRangeNode* node) override;
	void visit(class ForIterNode* node) override;
	void visit(class ReturnNode* node) override;
	void visit(class BreakNode* node) override;
	void visit(class ContinueNode* node) override;

	void visit(class TypeNode* node) override;
	void visit(class SliceTypeNode* node) override;
	void visit(class ArrayTypeNode* node) override;
	void visit(class FnNode* node) override;
	void visit(class FnParamNode* node) override;
	void visit(class FnParamListNode* node) override;
	void visit(class LetNode* node) override;

	void visit(class CallOperatorNode* node) override;
	void visit(class CallParamListNode* node) override;
	void visit(class PreIncOperatorNode* node) override;
	void visit(class PreDecOperatorNode* node) override;
	void visit(class PostIncOperatorNode* node) override;
	void visit(class PostDecOperatorNode* node) override;
	void visit(class SubscriptOperatorNode* node) override;
	void visit(class MemberOperatorNode* node) override;
	void visit(class AddOperatorNode* node) override;
	void visit(class SubOperatorNode* node) override;
	void visit(class MulOperatorNode* node) override;
	void visit(class DivOperatorNode* node) override;
	void visit(class ModOperatorNode* node) override;
	void visit(class BitwiseAndOperatorNode* node) override;
	void visit(class BitwiseOrOperatorNode* node) override;
	void visit(class AndOperatorNode* node) override;
	void visit(class OrOperatorNode* node) override;
	void visit(class EqOperatorNode* node) override;
	void visit(class NeOperatorNode* node) override;
	void visit(class LtOperatorNode* node) override;
	void visit(class LeOperatorNode* node) override;
	void visit(class GtOperatorNode* node) override;
	void visit(class GeOperatorNode* node) override;
	void visit(class InclusiveRangeOperatorNode* node) override;
	void visit(class ExclusiveRangeOperatorNode* node) override;

	void visit(class StringNode* node) override;
	void visit(class FloatNode* node) override;
	void visit(class IntNode* node) override;
	void visit(class SymbolNode* node) override;
	void visit(class ArrayNode* node) override;

	bool visit_next(class AbstractNode* node);

private:
	enum State {
		BUILD_GLOBAL_SCOPE,
		BUILD_FUNCTION_DEFINITION,
		BUILD_FUNCTION_PARAMETERS,
		BUILD_FUNCTION_BODY,
	};
	State m_state = BUILD_GLOBAL_SCOPE;

	llvm::LLVMContext m_context;
	llvm::IRBuilder<> m_builder;
};

#endif // BUILDNODEVISITOR_H
