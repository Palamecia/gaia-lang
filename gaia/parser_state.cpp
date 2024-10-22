#include "parser_state.h"
#include "lexer.h"

#include "node/constant_node.h"
#include <print>

ParserState::ParserState(std::unique_ptr<Lexer> lexer) :
	m_lexer(std::move(lexer)) {}

auto ParserState::next_token(std::unique_ptr<AbstractNode>* node) -> int {
	const auto [id, text] = m_lexer->next_token();
	switch (id) {
	case yy::parser::token::STRING_TOKEN:
		*node = std::unique_ptr<AbstractNode>(new StringNode(text));
		break;
	case yy::parser::token::FLOAT_TOKEN:
		*node = std::unique_ptr<AbstractNode>(new FloatNode(text));
		break;
	case yy::parser::token::INT_TOKEN:
		*node = std::unique_ptr<AbstractNode>(new IntNode(text));
		break;
	case yy::parser::token::SYMBOL_TOKEN:
		*node = std::unique_ptr<AbstractNode>(new SymbolNode(text));
		break;
	default:
		*node = nullptr;
		break;
	}
	return id;
}

void ParserState::print_error(std::string_view msg) {
	std::println(stderr, "{}", m_lexer->format_error(msg));
}

auto ParserState::get_ast() const -> AbstractNode& {
	return *m_ast;
}

void ParserState::set_ast(std::unique_ptr<AbstractNode> ast) {
	m_ast = std::move(ast);
}
