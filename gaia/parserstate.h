#ifndef PARSERSTATE_H
#define PARSERSTATE_H

#include "node/abstractnode.h"
#include <memory>
#include <string>

class Lexer;

class ParserState {
public:
	ParserState(std::unique_ptr<Lexer> lexer);

	int next_token(AbstractNode** node);

	void print_error(std::string const& msg);

	AbstractNode* get_ast() const;
	void set_ast(AbstractNode* ast);

private:
	std::unique_ptr<Lexer> m_lexer;
	std::unique_ptr<AbstractNode> m_ast;
};

#endif // PARSERSTATE_H
