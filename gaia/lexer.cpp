#include "lexer.h"

const std::unordered_map<std::string, yy::parser::token::token_kind_type> Lexer::KEYWORDS = {
	{ "break", yy::parser::token::BREAK_TOKEN },
	{ "case", yy::parser::token::CASE_TOKEN },
	{ "class", yy::parser::token::CLASS_TOKEN },
	{ "continue", yy::parser::token::CONTINUE_TOKEN },
	{ "default", yy::parser::token::DEFAULT_TOKEN },
	{ "else", yy::parser::token::ELSE_TOKEN },
	{ "fn", yy::parser::token::FN_TOKEN },
	{ "for", yy::parser::token::FOR_TOKEN },
	{ "guard", yy::parser::token::GUARD_TOKEN },
	{ "if", yy::parser::token::IF_TOKEN },
	{ "in", yy::parser::token::IN_TOKEN },
	{ "let", yy::parser::token::LET_TOKEN },
	{ "mut", yy::parser::token::MUT_TOKEN },
	{ "return", yy::parser::token::RETURN_TOKEN },
	{ "switch", yy::parser::token::SWITCH_TOKEN },
	{ "while", yy::parser::token::WHILE_TOKEN },
};

const std::unordered_map<std::string, yy::parser::token::token_kind_type> Lexer::OPERATORS = {
	{ "!", yy::parser::token::EXCLAMATION_TOKEN },
	{ "!=", yy::parser::token::EXCLAMATION_EQUAL_TOKEN },
	{ "%", yy::parser::token::PERCENT_TOKEN },
	{ "&", yy::parser::token::AMP_TOKEN },
	{ "&", yy::parser::token::AMP_TOKEN },
	{ "&&", yy::parser::token::DBL_AMP_TOKEN },
	{ "(", yy::parser::token::LEFT_PARENTHESIS_TOKEN },
	{ ")", yy::parser::token::RIGHT_PARENTHESIS_TOKEN },
	{ "*", yy::parser::token::ASTERISK_TOKEN },
	{ "+", yy::parser::token::PLUS_TOKEN },
	{ "++", yy::parser::token::DBL_PLUS_TOKEN },
	{ ",", yy::parser::token::COMMA_TOKEN },
	{ "-", yy::parser::token::MINUS_TOKEN },
	{ "--", yy::parser::token::DBL_MINUS_TOKEN },
	{ "->", yy::parser::token::ARROW_TOKEN },
	{ ".", yy::parser::token::DOT_TOKEN },
	{ "..", yy::parser::token::DBL_DOT_TOKEN },
	{ "...", yy::parser::token::TPL_DOT_TOKEN },
	{ "/", yy::parser::token::SLASH_TOKEN },
	{ "/*", yy::parser::token::COMMENT_TOKEN },
	{ "//", yy::parser::token::COMMENT_TOKEN },
	{ ":", yy::parser::token::COLON_TOKEN },
	{ "::", yy::parser::token::DBL_COLON_TOKEN },
	{ ";", yy::parser::token::SEMICOLON_TOKEN },
	{ "<", yy::parser::token::LEFT_ANGLED_TOKEN },
	{ "<=", yy::parser::token::LEFT_ANGLED_EQUAL_TOKEN },
	{ "=", yy::parser::token::EQUAL_TOKEN },
	{ "==", yy::parser::token::DBL_EQUAL_TOKEN },
	{ ">", yy::parser::token::RIGHT_ANGLED_TOKEN },
	{ ">=", yy::parser::token::RIGHT_ANGLED_EQUAL_TOKEN },
	{ "?", yy::parser::token::QUESTION_TOKEN },
	{ "[", yy::parser::token::LEFT_BRACKET_TOKEN },
	{ "]", yy::parser::token::RIGHT_BRACKET_TOKEN },
	{ "{", yy::parser::token::LEFT_BRACE_TOKEN },
	{ "|", yy::parser::token::PIPE_TOKEN },
	{ "||", yy::parser::token::DBL_PIPE_TOKEN },
	{ "}", yy::parser::token::RIGHT_BRACE_TOKEN },
};

Lexer::Lexer(DocumentStream *stream) :
	m_stream(stream),
	m_cptr(0),
	m_remaining(0) {

}

std::tuple<yy::parser::token::token_kind_type, std::string> Lexer::next_token() {

	while (is_space(static_cast<char>(m_cptr))) {
		m_cptr = m_stream->get_char();
	}

	std::string token;
	yy::parser::token::token_kind_type token_type = yy::parser::token::YYEMPTY;
	enum SearchMode { FIND_OPERATOR, FIND_NUMBER, FIND_IDENTIFIER };
	SearchMode find_mode = is_operator(std::string({static_cast<char>(m_cptr)}), token_type) ? FIND_OPERATOR : is_digit(m_cptr) ? FIND_NUMBER : FIND_IDENTIFIER;

	if (m_remaining) {
		token += static_cast<char>(m_remaining);
		m_remaining = 0;
	}

	switch (m_cptr) {
	case EOF:
		return {yy::parser::token::YYEOF, {}};
	case '\'':
	case '"':
		return { yy::parser::token::STRING_TOKEN, tokenize_string(static_cast<char>(m_cptr)) };
	default:
		break;
	}

	switch (find_mode) {
	case FIND_OPERATOR:
		while (!is_space(static_cast<char>(m_cptr)) && (m_cptr != EOF)
			   && is_operator(token + static_cast<char>(m_cptr), token_type)) {
			token += static_cast<char>(m_cptr);
			m_cptr = m_stream->get_char();
		}

		switch (token_type) {
		case yy::parser::token::COMMENT_TOKEN:
			if (token == "//") {
				while (m_cptr != '\n' && m_cptr != EOF) {
					m_cptr = m_stream->get_char();
				}
				return next_token();
			}

			if (token == "/*") {
				for (;;) {
					while (m_cptr != '*' && m_cptr != EOF) {
						m_cptr = m_stream->get_char();
					}
					switch ((m_cptr = m_stream->get_char())) {
					case '/':
						m_cptr = m_stream->get_char();
						return next_token();
					case EOF:
						return {};
					default:
						break;
					}
				}
			}
			break;

		default:
			break;
		}
		break;

	case FIND_NUMBER:
		while (!is_space(static_cast<char>(m_cptr)) && (m_cptr != EOF)
			   && is_digit(m_cptr)) {
			token += static_cast<char>(m_cptr);
			m_cptr = m_stream->get_char();
		}

		token_type = yy::parser::token::INT_TOKEN;

		if (m_cptr == 'b' || m_cptr == 'B' || m_cptr == 'o' || m_cptr == 'O' || m_cptr == 'x' || m_cptr == 'X') {
			while (!is_space(static_cast<char>(m_cptr)) && (m_cptr != EOF)
				   && !is_operator(std::string({static_cast<char>(m_cptr)}))) {
				token += static_cast<char>(m_cptr);
				m_cptr = m_stream->get_char();
			}
		}
		else {
			if (m_cptr == '.') {
				std::string decimals = ".";
				m_cptr = m_stream->get_char();
				if (is_operator(decimals + static_cast<char>(m_cptr))) {
					m_remaining = '.';
					return { yy::parser::token::FLOAT_TOKEN, token };
				}
				while (is_digit(m_cptr)) {
					decimals += static_cast<char>(m_cptr);
					m_cptr = m_stream->get_char();
				}
				token_type = yy::parser::token::FLOAT_TOKEN;
				token += decimals;
			}
			if (m_cptr == 'e' || m_cptr == 'E') {
				std::string exponent = std::string({static_cast<char>(m_cptr)});
				m_cptr = m_stream->get_char();
				if (m_cptr == '+' || m_cptr == '-') {
					exponent += static_cast<char>(m_cptr);
					m_cptr = m_stream->get_char();
				}
				while (is_digit(m_cptr)) {
					exponent += static_cast<char>(m_cptr);
					m_cptr = m_stream->get_char();
				}
				token_type = yy::parser::token::FLOAT_TOKEN;
				token += exponent;
			}
		}
		break;

	case FIND_IDENTIFIER:
		while (!is_space(static_cast<char>(m_cptr)) && (m_cptr != EOF)
			   && !is_operator(std::string({static_cast<char>(m_cptr)}))) {
			token += static_cast<char>(m_cptr);
			m_cptr = m_stream->get_char();
		}
		if (auto it = KEYWORDS.find(token); it != KEYWORDS.end()) {
			token_type = it->second;
		}
		else {
			token_type =yy::parser::token::SYMBOL_TOKEN;
		}
		break;
	}

	return {token_type, token};
}

std::string Lexer::format_error(const char *error) const {

	auto path = m_stream->get_path();
	auto line_number = m_stream->get_line_number();
	auto column_number = m_stream->get_column_number();
	auto line_error = m_stream->get_current_line();

	return path + ":"  + std::to_string(line_number) + ":"  + std::to_string(column_number) + " " + error + "\n" + line_error;
}

bool Lexer::at_end() const {
	return m_stream->at_end();
}

bool Lexer::is_digit(int c) {
#ifdef BUILD_TYPE_DEBUG
	return isascii(c) && isdigit(c);
#else
	return isdigit(c);
#endif
}

bool Lexer::is_space(int c) {
#ifdef BUILD_TYPE_DEBUG
	return (isascii(c) && isspace(c)) || c == 0;
#else
	return isspace(c) || c == 0;
#endif
}

bool Lexer::is_operator(std::string const& token) {
	return OPERATORS.find(token) != OPERATORS.end();
}

bool Lexer::is_operator(std::string const& token, yy::parser::token::token_kind_type& type) {

	auto it = OPERATORS.find(token);

	if (it != OPERATORS.end()) {
		type = it->second;
		return true;
	}

	return false;
}

std::string Lexer::tokenize_string(char delim) {

	std::string token;
	bool shift = false;

	do {
		if (m_cptr == EOF) {
			return token;
		}
		token += static_cast<char>(m_cptr);
		shift = ((m_cptr == '\\') && !shift);
	} while (((m_cptr = m_stream->get_char()) != delim) || shift);
	token += static_cast<char>(m_cptr);

	m_cptr = m_stream->get_char();
	return token;
}
