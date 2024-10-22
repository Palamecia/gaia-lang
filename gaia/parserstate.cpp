#include "parserstate.h"
#include "parser.h"
#include "lexer.h"

#include "node/constantnode.h"

ParserState::ParserState(std::unique_ptr<Lexer> lexer) :
	m_lexer(std::move(lexer)) {

}

int ParserState::next_token(AbstractNode** node) {
	auto [id, text] = m_lexer->next_token();
	switch (id) {
	case yy::parser::token::STRING_TOKEN:
		*node = new StringNode(text);
		break;
	case yy::parser::token::FLOAT_TOKEN:
		*node = new FloatNode(text);
		break;
	case yy::parser::token::INT_TOKEN:
		*node = new IntNode(text);
		break;
	case yy::parser::token::SYMBOL_TOKEN:
		*node = new SymbolNode(text);
		break;
	default:
		*node = nullptr;
		break;
	}
	return id;
}

void ParserState::print_error(std::string const& msg) {
	fprintf(stderr, "%s\n", m_lexer->format_error(msg.c_str()).c_str());
}

AbstractNode* ParserState::get_ast() const {
	return m_ast.get();
}

void ParserState::set_ast(AbstractNode* ast) {
	m_ast.reset(ast);
}
