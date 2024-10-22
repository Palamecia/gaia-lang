#include "abstractnodevisitor.h"

AbstractNodeVisitor::AbstractNodeVisitor() {}

void AbstractNodeVisitor::visit(StmtListNode* node) {}
void AbstractNodeVisitor::visit(IfElseNode* node) {}
void AbstractNodeVisitor::visit(SwitchNode* node) {}
void AbstractNodeVisitor::visit(CaseListNode* node) {}
void AbstractNodeVisitor::visit(CaseNode* node) {}
void AbstractNodeVisitor::visit(DefaultNode* node) {}
void AbstractNodeVisitor::visit(WhileNode* node) {}
void AbstractNodeVisitor::visit(ForRangeNode* node) {}
void AbstractNodeVisitor::visit(ForIterNode* node) {}
void AbstractNodeVisitor::visit(ReturnNode* node) {}
void AbstractNodeVisitor::visit(BreakNode* node) {}
void AbstractNodeVisitor::visit(ContinueNode* node) {}
void AbstractNodeVisitor::visit(TypeNode* node) {}
void AbstractNodeVisitor::visit(SliceTypeNode* node) {}
void AbstractNodeVisitor::visit(ArrayTypeNode* node) {}
void AbstractNodeVisitor::visit(FnNode* node) {}
void AbstractNodeVisitor::visit(FnParamNode* node) {}
void AbstractNodeVisitor::visit(FnParamListNode* node) {}
void AbstractNodeVisitor::visit(LetNode* node) {}
void AbstractNodeVisitor::visit(CallOperatorNode* node) {}
void AbstractNodeVisitor::visit(CallParamListNode* node) {}
void AbstractNodeVisitor::visit(PreIncOperatorNode* node) {}
void AbstractNodeVisitor::visit(PreDecOperatorNode* node) {}
void AbstractNodeVisitor::visit(PostIncOperatorNode* node) {}
void AbstractNodeVisitor::visit(PostDecOperatorNode* node) {}
void AbstractNodeVisitor::visit(PosOperatorNode* node) {}
void AbstractNodeVisitor::visit(NegOperatorNode* node) {}
void AbstractNodeVisitor::visit(NotOperatorNode* node) {}
void AbstractNodeVisitor::visit(InvOperatorNode* node) {}
void AbstractNodeVisitor::visit(SubscriptOperatorNode* node) {}
void AbstractNodeVisitor::visit(ScopeOperatorNode* node) {}
void AbstractNodeVisitor::visit(MemberOperatorNode* node) {}
void AbstractNodeVisitor::visit(AddOperatorNode* node) {}
void AbstractNodeVisitor::visit(SubOperatorNode* node) {}
void AbstractNodeVisitor::visit(MulOperatorNode* node) {}
void AbstractNodeVisitor::visit(DivOperatorNode* node) {}
void AbstractNodeVisitor::visit(ModOperatorNode* node) {}
void AbstractNodeVisitor::visit(BitwiseAndOperatorNode* node) {}
void AbstractNodeVisitor::visit(BitwiseXorOperatorNode* node) {}
void AbstractNodeVisitor::visit(BitwiseOrOperatorNode* node) {}
void AbstractNodeVisitor::visit(AndOperatorNode* node) {}
void AbstractNodeVisitor::visit(OrOperatorNode* node) {}
void AbstractNodeVisitor::visit(EqOperatorNode* node) {}
void AbstractNodeVisitor::visit(NeOperatorNode* node) {}
void AbstractNodeVisitor::visit(LtOperatorNode* node) {}
void AbstractNodeVisitor::visit(LeOperatorNode* node) {}
void AbstractNodeVisitor::visit(GtOperatorNode* node) {}
void AbstractNodeVisitor::visit(GeOperatorNode* node) {}
void AbstractNodeVisitor::visit(ShiftLeftOperatorNode* node) {}
void AbstractNodeVisitor::visit(ShiftRightOperatorNode* node) {}
void AbstractNodeVisitor::visit(InclusiveRangeOperatorNode* node) {}
void AbstractNodeVisitor::visit(ExclusiveRangeOperatorNode* node) {}
void AbstractNodeVisitor::visit(StringNode* node) {}
void AbstractNodeVisitor::visit(FloatNode* node) {}
void AbstractNodeVisitor::visit(IntNode* node) {}
void AbstractNodeVisitor::visit(SymbolNode* node) {}
void AbstractNodeVisitor::visit(ArrayNode* node) {}