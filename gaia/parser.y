%code requires {
#include <parserstate.h>
#include <node/constantnode.h>
#include <node/declnode.h>
#include <node/flownode.h>
#include <node/operatornode.h>

#define YYSTYPE AbstractNode *
}

%code top {
#define yylex self->next_token
}

%parse-param {ParserState *self}

%token COMMENT_TOKEN
%token SYMBOL_TOKEN STRING_TOKEN FLOAT_TOKEN INT_TOKEN
%token CLASS_TOKEN FN_TOKEN LET_TOKEN MUT_TOKEN
%token GUARD_TOKEN IF_TOKEN ELSE_TOKEN WHILE_TOKEN FOR_TOKEN IN_TOKEN SWITCH_TOKEN CASE_TOKEN DEFAULT_TOKEN RETURN_TOKEN BREAK_TOKEN CONTINUE_TOKEN

%token ARROW_TOKEN SEMICOLON_TOKEN


%left COMMA_TOKEN
%right EQUAL_TOKEN QUESTION_TOKEN COLON_TOKEN PLUS_EQUAL_TOKEN MINUS_EQUAL_TOKEN ASTERISK_EQUAL_TOKEN SLASH_EQUAL_TOKEN PERCENT_EQUAL_TOKEN DBL_LEFT_ANGLED_EQUAL_TOKEN DBL_RIGHT_ANGLED_EQUAL_TOKEN AMP_EQUAL_TOKEN PIPE_EQUAL_TOKEN CARET_EQUAL_TOKEN
%left DBL_PIPE_TOKEN
%left DBL_AMP_TOKEN
%left PIPE_TOKEN
%left CARET_TOKEN
%left AMP_TOKEN
%left DBL_DOT_TOKEN TPL_DOT_TOKEN
%left DBL_EQUAL_TOKEN EXCLAMATION_EQUAL_TOKEN IS_TOKEN
%left LEFT_ANGLED_TOKEN RIGHT_ANGLED_TOKEN LEFT_ANGLED_EQUAL_TOKEN RIGHT_ANGLED_EQUAL_TOKEN
%left DBL_LEFT_ANGLED_TOKEN DBL_RIGHT_ANGLED_TOKEN
%left PLUS_TOKEN MINUS_TOKEN
%left ASTERISK_TOKEN SLASH_TOKEN PERCENT_TOKEN
%right PREFIX_DBL_PLUS_TOKEN PREFIX_DBL_MINUS_TOKEN PREFIX_PLUS_TOKEN PREFIX_MINUS_TOKEN EXCLAMATION_TOKEN TILDE_TOKEN
%left DBL_PLUS_TOKEN DBL_MINUS_TOKEN DOT_TOKEN LEFT_PARENTHESIS_TOKEN RIGHT_PARENTHESIS_TOKEN LEFT_BRACKET_TOKEN RIGHT_BRACKET_TOKEN LEFT_BRACE_TOKEN RIGHT_BRACE_TOKEN
%left DBL_COLON_TOKEN

%%

module_rule:
    decl_list_rule YYEOF {
	    self->set_ast($1);
		fflush(stdout);
		YYACCEPT;
	}
	| YYEOF {
	    self->set_ast(new StmtListNode);
		fflush(stdout);
		YYACCEPT;
	};

stmt_list_rule:
    stmt_list_rule stmt_rule {
	    $$ = $1;
		static_cast<StmtListNode*>($$)->append($2);
	}
	| stmt_rule {
	    $$ = new StmtListNode();
		static_cast<StmtListNode*>($$)->append($1);
	};

stmt_block_rule:
    LEFT_BRACE_TOKEN stmt_list_rule RIGHT_BRACE_TOKEN {
	    $$ = $2;
	}
	| LEFT_BRACE_TOKEN RIGHT_BRACE_TOKEN {
	    $$ = new StmtListNode();
	};

stmt_rule:
    LET_TOKEN MUT_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN FOR_TOKEN variable_name_rule IN_TOKEN expr_rule stmt_block_rule {
	    auto generator = new ForRangeNode($8, $10);
		generator->set_branch($11);
		$$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_type($5);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN FOR_TOKEN variable_name_rule IN_TOKEN expr_rule stmt_block_rule {
	    auto generator = new ForRangeNode($7, $9);
		generator->set_branch($10);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_type($4);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule EQUAL_TOKEN FOR_TOKEN variable_name_rule IN_TOKEN expr_rule stmt_block_rule {
	    auto generator = new ForRangeNode($6, $8);
		generator->set_branch($9);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule EQUAL_TOKEN FOR_TOKEN variable_name_rule IN_TOKEN expr_rule stmt_block_rule {
	    auto generator = new ForRangeNode($5, $7);
		generator->set_branch($8);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| SYMBOL_TOKEN COLON_TOKEN FOR_TOKEN variable_name_rule IN_TOKEN expr_rule stmt_block_rule {
	    $$ = new ForRangeNode($4, $6);
		static_cast<ForRangeNode*>($$)->set_label($1);
		static_cast<ForRangeNode*>($$)->set_branch($7);
	}
	| FOR_TOKEN variable_name_rule IN_TOKEN expr_rule stmt_block_rule {
	    $$ = new ForRangeNode($2, $4);
		static_cast<ForRangeNode*>($$)->set_branch($5);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN FOR_TOKEN init_expr_rule SEMICOLON_TOKEN opt_expr_rule SEMICOLON_TOKEN opt_expr_rule stmt_block_rule {
	    auto generator = new ForIterNode($8, $10, $12);
		generator->set_branch($13);
		$$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_type($5);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN FOR_TOKEN init_expr_rule SEMICOLON_TOKEN opt_expr_rule SEMICOLON_TOKEN opt_expr_rule stmt_block_rule {
	    auto generator = new ForIterNode($7, $9, $11);
		generator->set_branch($12);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_type($4);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule EQUAL_TOKEN FOR_TOKEN init_expr_rule SEMICOLON_TOKEN opt_expr_rule SEMICOLON_TOKEN opt_expr_rule stmt_block_rule {
	    auto generator = new ForIterNode($6, $8, $10);
		generator->set_branch($11);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule EQUAL_TOKEN FOR_TOKEN init_expr_rule SEMICOLON_TOKEN opt_expr_rule SEMICOLON_TOKEN opt_expr_rule stmt_block_rule {
	    auto generator = new ForIterNode($5, $7, $9);
		generator->set_branch($10);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| SYMBOL_TOKEN COLON_TOKEN FOR_TOKEN init_expr_rule SEMICOLON_TOKEN opt_expr_rule SEMICOLON_TOKEN opt_expr_rule stmt_block_rule {
	    $$ = new ForIterNode($4, $6, $8);
		static_cast<ForIterNode*>($$)->set_label($1);
		static_cast<ForIterNode*>($$)->set_branch($9);
	}
	| FOR_TOKEN init_expr_rule SEMICOLON_TOKEN opt_expr_rule SEMICOLON_TOKEN opt_expr_rule stmt_block_rule {
	    $$ = new ForIterNode($2, $4, $6);
		static_cast<ForRangeNode*>($$)->set_branch($7);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN WHILE_TOKEN expr_rule stmt_block_rule {
	    auto generator = new WhileNode($8);
		generator->set_branch($9);
		$$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_type($5);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN WHILE_TOKEN expr_rule stmt_block_rule {
	    auto generator = new WhileNode($7);
		generator->set_branch($8);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_type($4);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule EQUAL_TOKEN WHILE_TOKEN expr_rule stmt_block_rule {
	    auto generator = new WhileNode($6);
		generator->set_branch($7);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule EQUAL_TOKEN WHILE_TOKEN expr_rule stmt_block_rule {
	    auto generator = new WhileNode($5);
		generator->set_branch($6);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| SYMBOL_TOKEN COLON_TOKEN WHILE_TOKEN expr_rule stmt_block_rule {
	    $$ = new WhileNode($4);
		static_cast<WhileNode*>($$)->set_label($1);
		static_cast<WhileNode*>($$)->set_branch($5);
	}
	| WHILE_TOKEN expr_rule stmt_block_rule {
	    $$ = new WhileNode($2);
		static_cast<WhileNode*>($$)->set_branch($3);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN SWITCH_TOKEN expr_rule case_block_rule {
	    auto generator = new SwitchNode($8);
		generator->set_branch($9);
		$$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_type($5);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN SWITCH_TOKEN expr_rule case_block_rule {
	    auto generator = new SwitchNode($7);
		generator->set_branch($8);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_type($4);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule EQUAL_TOKEN SWITCH_TOKEN expr_rule case_block_rule {
	    auto generator = new SwitchNode($6);
		generator->set_branch($7);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| LET_TOKEN variable_name_rule EQUAL_TOKEN SWITCH_TOKEN expr_rule case_block_rule {
	    auto generator = new SwitchNode($5);
		generator->set_branch($6);
		$$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_value(generator);
	}
	| SYMBOL_TOKEN COLON_TOKEN SWITCH_TOKEN expr_rule case_block_rule {
	    $$ = new SwitchNode($4);
		static_cast<SwitchNode*>($$)->set_label($1);
		static_cast<SwitchNode*>($$)->set_branch($5);
	}
	| SWITCH_TOKEN expr_rule case_block_rule {
	    $$ = new SwitchNode($2);
		static_cast<SwitchNode*>($$)->set_branch($3);
	}
	| IF_TOKEN expr_rule stmt_block_rule else_stmt_rule {
	    $$ = new IfElseNode($2);
		static_cast<IfElseNode*>($$)->set_true_branch($3);
		static_cast<IfElseNode*>($$)->set_false_branch($4);
	}
	| IF_TOKEN expr_rule stmt_block_rule {
	    $$ = new IfElseNode($2);
		static_cast<IfElseNode*>($$)->set_true_branch($3);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_type($5);
		static_cast<LetNode*>($$)->set_value($7);
	}
	| LET_TOKEN variable_name_rule COLON_TOKEN type_desc_rule EQUAL_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_type($4);
		static_cast<LetNode*>($$)->set_value($6);
	}
	| LET_TOKEN MUT_TOKEN variable_name_rule EQUAL_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_value($5);
	}
	| LET_TOKEN variable_name_rule EQUAL_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_value($4);
	}
	| RETURN_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new ReturnNode($2);
	}
	| CONTINUE_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new ContinueNode($2);
	}
	| BREAK_TOKEN expr_rule SEMICOLON_TOKEN {
	    $$ = new ContinueNode($2);
	}
	| RETURN_TOKEN SEMICOLON_TOKEN {
	    $$ = new ReturnNode();
	}
	| CONTINUE_TOKEN SEMICOLON_TOKEN {
	    $$ = new ContinueNode();
	}
	| BREAK_TOKEN SEMICOLON_TOKEN {
	    $$ = new ContinueNode();
	}
	| expr_rule SEMICOLON_TOKEN {
	    $$ = $1;
	}
	| stmt_block_rule {
	    $$ = $1;
	}
	| SEMICOLON_TOKEN;

case_list_rule:
    case_list_rule CASE_TOKEN expr_rule COLON_TOKEN stmt_list_rule {
	    auto node = new CaseNode($3);
		node->set_branch($5);
		$$ = $1;
		static_cast<CaseListNode*>($$)->append(node);
	}
	| CASE_TOKEN expr_rule COLON_TOKEN stmt_list_rule {
	    auto node = new CaseNode($2);
		node->set_branch($4);
		$$ = new CaseListNode();
		static_cast<CaseListNode*>($$)->append(node);
	};

case_block_rule:
    LEFT_BRACE_TOKEN case_list_rule DEFAULT_TOKEN COLON_TOKEN stmt_list_rule RIGHT_BRACE_TOKEN {
	    auto node = new DefaultNode();
		node->set_branch($5);
		$$ = $2;
		static_cast<CaseListNode*>($$)->append(node);
	}
	| LEFT_BRACE_TOKEN case_list_rule RIGHT_BRACE_TOKEN {
	    $$ = $2;
	}
	| LEFT_BRACE_TOKEN RIGHT_BRACE_TOKEN {
	    $$ = new CaseListNode();
	};

else_stmt_rule:
    ELSE_TOKEN IF_TOKEN expr_rule stmt_block_rule else_stmt_rule {
	    $$ = new IfElseNode($3);
		static_cast<IfElseNode*>($$)->set_true_branch($4);
		static_cast<IfElseNode*>($$)->set_false_branch($5);
	}
	| ELSE_TOKEN IF_TOKEN expr_rule stmt_block_rule {
	    $$ = new IfElseNode($3);
		static_cast<IfElseNode*>($$)->set_true_branch($4);
	}
	| ELSE_TOKEN stmt_block_rule {
	    $$ = $2;
	};

decl_list_rule:
    decl_list_rule decl_rule {
		$$ = $1;
		static_cast<StmtListNode*>($$)->append($2);
	}
	| decl_rule {
	    $$ = new StmtListNode();
		static_cast<StmtListNode*>($$)->append($1);
	};

decl_rule:
    class_decl_rule {

    }
	| fn_decl_rule {
	    $$ = $1;
    };

type_desc_rule:
    type_desc_rule QUESTION_TOKEN {
	    $$ = $1;
		static_cast<DeclNode*>($$)->set_flag(DeclNode::OPT_FLAG);
	}
	| type_desc_rule ASTERISK_TOKEN {
	    $$ = $1;
		static_cast<DeclNode*>($$)->set_flag(DeclNode::PTR_FLAG);
	}
	| type_desc_rule AMP_TOKEN {
	    $$ = $1;
		static_cast<DeclNode*>($$)->set_flag(DeclNode::MOVE_FLAG);
	}
	| type_desc_rule EXCLAMATION_TOKEN {
	    $$ = $1;
		static_cast<DeclNode*>($$)->set_flag(DeclNode::COPY_FLAG);
	}
	| LEFT_BRACKET_TOKEN type_desc_rule SEMICOLON_TOKEN expr_rule RIGHT_BRACKET_TOKEN {
	    $$ = new ArrayTypeNode($2, $4);
	}
	| LEFT_BRACKET_TOKEN type_desc_rule RIGHT_BRACKET_TOKEN {
	    $$ = new SliceTypeNode($2);
	}
	| SYMBOL_TOKEN {
	    $$ = new TypeNode($1);
	};

variable_name_rule:
    SYMBOL_TOKEN {
	    $$ = $1;
	};

class_decl_rule:
    CLASS_TOKEN {

    };

fn_decl_rule:
    fn_sig_decl_rule LEFT_BRACE_TOKEN stmt_list_rule RIGHT_BRACE_TOKEN {
	    $$ = $1;
		static_cast<FnNode*>($$)->set_body($3);
    };

fn_sig_decl_rule:
    FN_TOKEN SYMBOL_TOKEN LEFT_PARENTHESIS_TOKEN fn_param_decl_rule RIGHT_PARENTHESIS_TOKEN ARROW_TOKEN type_desc_rule {
	    $$ = new FnNode($2);
		static_cast<FnNode*>($$)->set_parameters($4);
		static_cast<FnNode*>($$)->set_type($7);
    }
	| FN_TOKEN SYMBOL_TOKEN LEFT_PARENTHESIS_TOKEN fn_param_decl_rule RIGHT_PARENTHESIS_TOKEN {
	    $$ = new FnNode($2);
		static_cast<FnNode*>($$)->set_parameters($4);
    };

fn_param_decl_rule:
    fn_param_decl_rule COMMA_TOKEN SYMBOL_TOKEN COLON_TOKEN type_desc_rule {
	    auto param = new FnParamNode($1, $3);
		static_cast<CallParamListNode*>($$)->append(param);
	}
	| fn_param_decl_rule COMMA_TOKEN SYMBOL_TOKEN COLON_TOKEN type_desc_rule EQUAL_TOKEN expr_rule {
	    auto param = new FnParamNode($1, $3);
		param->set_default_value($7);
		static_cast<CallParamListNode*>($$)->append(param);
	}
	| SYMBOL_TOKEN COLON_TOKEN type_desc_rule {
	    $$ = new FnParamListNode();
		auto param = new FnParamNode($1, $3);
		static_cast<CallParamListNode*>($$)->append(param);
	}
	| SYMBOL_TOKEN COLON_TOKEN type_desc_rule EQUAL_TOKEN expr_rule {
	    $$ = new FnParamListNode();
		auto param = new FnParamNode($1, $3);
		param->set_default_value($5);
		static_cast<CallParamListNode*>($$)->append(param);
	}
	| {
	    $$ = new FnParamListNode();
	};

init_expr_rule:
    LET_TOKEN MUT_TOKEN SYMBOL_TOKEN COLON_TOKEN type_desc_rule EQUAL_TOKEN expr_rule {
	    $$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_type($5);
		static_cast<LetNode*>($$)->set_value($7);
	}
	| LET_TOKEN SYMBOL_TOKEN COLON_TOKEN type_desc_rule EQUAL_TOKEN expr_rule {
	    $$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_type($4);
		static_cast<LetNode*>($$)->set_value($6);
	}
	| LET_TOKEN MUT_TOKEN SYMBOL_TOKEN EQUAL_TOKEN expr_rule {
	    $$ = new LetNode($3);
		static_cast<LetNode*>($$)->set_flag(LetNode::MUT_FLAG);
		static_cast<LetNode*>($$)->set_value($5);
	}
	| LET_TOKEN SYMBOL_TOKEN EQUAL_TOKEN expr_rule {
	    $$ = new LetNode($2);
		static_cast<LetNode*>($$)->set_value($4);
	}
	| opt_expr_rule {
	    $$ = $1;
	};

opt_expr_rule:
    expr_rule {
	    $$ = $1;
	}
	| {
	    $$ = nullptr;
	};

expr_rule:
    expr_rule DBL_COLON_TOKEN expr_rule {
	    $$ = new ScopeOperatorNode($1, $3);
	}
	| expr_rule DBL_PLUS_TOKEN {
	    $$ = new PostIncOperatorNode($2);
	}
	| expr_rule DBL_MINUS_TOKEN {
	    $$ = new PostDecOperatorNode($2);
	}
	| expr_rule LEFT_PARENTHESIS_TOKEN expr_param_rule RIGHT_PARENTHESIS_TOKEN {
	    $$ = new CallOperatorNode($1, $3);
	}
	| expr_rule LEFT_BRACKET_TOKEN expr_rule RIGHT_BRACKET_TOKEN {
	    $$ = new SubscriptOperatorNode($1, $3);
	}
	| expr_rule DOT_TOKEN expr_rule {
	    $$ = new MemberOperatorNode($1, $3);
	}
	| DBL_PLUS_TOKEN expr_rule %prec PREFIX_DBL_PLUS_TOKEN {
	    $$ = new PreIncOperatorNode($2);
	}
	| DBL_MINUS_TOKEN expr_rule %prec PREFIX_DBL_MINUS_TOKEN {
	    $$ = new PreDecOperatorNode($2);
	}
	| PLUS_TOKEN expr_rule %prec PREFIX_PLUS_TOKEN {
	    $$ = new PosOperatorNode($2);
	}
	| MINUS_TOKEN expr_rule %prec PREFIX_MINUS_TOKEN {
	    $$ = new NegOperatorNode($2);
	}
	| EXCLAMATION_TOKEN expr_rule {
	    $$ = new NotOperatorNode($2);
	}
	| TILDE_TOKEN expr_rule {
	    $$ = new InvOperatorNode($2);
	}
	| expr_rule ASTERISK_TOKEN expr_rule {
	    $$ = new MulOperatorNode($1, $3);
	}
	| expr_rule SLASH_TOKEN expr_rule {
	    $$ = new DivOperatorNode($1, $3);
	}
	| expr_rule PERCENT_TOKEN expr_rule {
	    $$ = new ModOperatorNode($1, $3);
	}
	| expr_rule PLUS_TOKEN expr_rule {
	    $$ = new AddOperatorNode($1, $3);
	}
	| expr_rule MINUS_TOKEN expr_rule {
	    $$ = new SubOperatorNode($1, $3);
	}
	| expr_rule DBL_LEFT_ANGLED_TOKEN expr_rule {
	    $$ = new ShiftLeftOperatorNode($1, $3);
	}
	| expr_rule DBL_RIGHT_ANGLED_TOKEN expr_rule {
	    $$ = new ShiftRightOperatorNode($1, $3);
	}
	| expr_rule LEFT_ANGLED_TOKEN expr_rule {
	    $$ = new LtOperatorNode($1, $3);
	}
	| expr_rule LEFT_ANGLED_EQUAL_TOKEN expr_rule {
	    $$ = new LeOperatorNode($1, $3);
	}
	| expr_rule RIGHT_ANGLED_TOKEN expr_rule {
	    $$ = new GtOperatorNode($1, $3);
	}
	| expr_rule RIGHT_ANGLED_EQUAL_TOKEN expr_rule {
	    $$ = new GeOperatorNode($1, $3);
	}
	| expr_rule DBL_EQUAL_TOKEN expr_rule {
	    $$ = new EqOperatorNode($1, $3);
	}
	| expr_rule EXCLAMATION_EQUAL_TOKEN expr_rule {
	    $$ = new NeOperatorNode($1, $3);
	}
	| expr_rule AMP_TOKEN expr_rule {
	    $$ = new BitwiseAndOperatorNode($1, $3);
	}
	| expr_rule CARET_TOKEN expr_rule {
	    $$ = new BitwiseXorOperatorNode($1, $3);
	}
	| expr_rule PIPE_TOKEN expr_rule {
	    $$ = new BitwiseOrOperatorNode($1, $3);
	}
	| expr_rule DBL_AMP_TOKEN expr_rule {
	    $$ = new AndOperatorNode($1, $3);
	}
	| expr_rule DBL_PIPE_TOKEN expr_rule {
	    $$ = new OrOperatorNode($1, $3);
	}
	| expr_rule DBL_DOT_TOKEN expr_rule {
	    $$ = new InclusiveRangeOperatorNode($1, $3);
	}
	| expr_rule TPL_DOT_TOKEN expr_rule {
	    $$ = new ExclusiveRangeOperatorNode($1, $3);
	}
	| LEFT_BRACKET_TOKEN expr_param_rule RIGHT_BRACKET_TOKEN {
	    $$ = new ArrayNode($2);
	}
	| constant_rule {
	    $$ = $1;
	};

expr_param_rule:
    expr_param_rule COMMA_TOKEN expr_rule {
	    static_cast<CallParamListNode*>($$)->append($3);
	}
	| expr_rule {
	    $$ = new CallParamListNode();
		static_cast<CallParamListNode*>($$)->append($1);
	}
	| {
	    $$ = new CallParamListNode();
	};

constant_rule:
    SYMBOL_TOKEN { $$ = $1; };
	| STRING_TOKEN { $$ = $1; }
	| FLOAT_TOKEN { $$ = $1; }
	| INT_TOKEN { $$ = $1; }

%%

void yy::parser::error(std::string const& msg) {
    self->print_error(msg);
}
