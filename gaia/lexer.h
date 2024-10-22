#ifndef LEXER_H
#define LEXER_H

#include "stream/documentstream.h"
#include "parser.h"

#include <functional>
#include <unordered_map>
#include <string_view>
#include <string>

class Lexer {
public:
	Lexer(const Lexer&) = delete;
	Lexer(Lexer&&) = delete;
	Lexer(DocumentStream& stream);
	~Lexer() = default;

	auto operator=(const Lexer&) -> Lexer& = delete;
	auto operator=(Lexer&&) -> Lexer& = delete;

	auto next_token() -> std::tuple<yy::parser::token::token_kind_type, std::string>;

	auto format_error(std::string_view error) const -> std::string;
	auto at_end() const -> bool;

	static auto is_digit(int c) -> bool;
	static auto is_space(int c) -> bool;
	static auto is_operator(std::string const& token) -> bool;
	static auto is_operator(std::string const& token, yy::parser::token::token_kind_type& type) -> bool;

protected:
	auto tokenize_string(char delim) -> std::string;

private:
	static const std::unordered_map<std::string, yy::parser::token::token_kind_type> KEYWORDS;
	static const std::unordered_map<std::string, yy::parser::token::token_kind_type> OPERATORS;

	DocumentStream& m_stream;
	std::string m_token;
	int m_cptr = 0;
	int m_remaining = 0; // hack
};

#endif // LEXER_H
