#ifndef LEXER_H
#define LEXER_H

#include "stream/documentstream.h"
#include "parser.h"

#include <unordered_map>
#include <string>

class Lexer {
public:
	Lexer(DocumentStream *stream);
	~Lexer() = default;

	std::tuple<yy::parser::token::token_kind_type, std::string> next_token();

	std::string format_error(const char *error) const;
	bool at_end() const;

	static bool is_digit(int c);
	static bool is_space(int c);
	static bool is_operator(std::string const& token);
	static bool is_operator(std::string const& token, yy::parser::token::token_kind_type& type);

protected:
	std::string tokenize_string(char delim);

private:
	static const std::unordered_map<std::string, yy::parser::token::token_kind_type> KEYWORDS;
	static const std::unordered_map<std::string, yy::parser::token::token_kind_type> OPERATORS;

	DocumentStream *m_stream;
	int m_cptr;
	int m_remaining; // hack
};

#endif // LEXER_H
