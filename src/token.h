#pragma once

#include <any>
#include <string>

#include "token_type.h"

namespace next {

class token {
public:
	explicit token(token_type type, std::string&& lexeme, std::any literal, int line) :
		m_type(type), m_lexeme(std::move(lexeme)), m_literal(literal), m_line(line) {}
	explicit token(token_type type, std::string&& lexeme, int line) :
		token(type, std::move(lexeme), std::any{}, line) {}

	[[maybe_unused]] std::string to_string() const;
	[[maybe_unused]] std::string literal_to_string() const;

private:
	token_type m_type;
	std::string m_lexeme;
	std::any m_literal;
	int m_line;
};

} // next