#ifndef PARSER_STATE_H
#define PARSER_STATE_H

#include "node/abstract_node.h"
#include <memory>
#include <string_view>

class Lexer;

class ParserState {
public:
	ParserState(std::unique_ptr<Lexer> lexer);

	auto next_token(std::unique_ptr<AbstractNode>* node) -> int;

	void print_error(std::string_view msg);

	[[nodiscard]] auto get_ast() const -> AbstractNode&;
	void set_ast(std::unique_ptr<AbstractNode> ast);

private:
	std::unique_ptr<Lexer> m_lexer;
	std::unique_ptr<AbstractNode> m_ast;
};

#endif // PARSER_STATE_H
