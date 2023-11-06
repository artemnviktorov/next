#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

#include "token_type.h"
#include "token.h"

namespace next {

class scanner {
public:
	explicit scanner(const std::string& src) : m_src(src) {}

	std::vector<token> scan_tokens();

private:
	int m_start = 0;
	int m_current = 0;
	int m_line = 1;

	std::string m_src;
	std::vector<token> m_tokens;
	std::unordered_map<std::string, token_type> m_keywords = {
		{"and", token_type::And},
		{"class", token_type::Class},
		{"else", token_type::Else},
		{"false", token_type::False},
		{"for", token_type::For},
		{"fun", token_type::Fun},
		{"if", token_type::If},
		{"nil", token_type::Nil},
		{"or", token_type::Or},
		{"print", token_type::Print},
		{"return", token_type::Return},
		{"super", token_type::Super},
		{"this", token_type::This},
		{"true", token_type::True},
		{"var", token_type::Var},
		{"while", token_type::While}
	};

	bool is_at_end() const;
	char advance();
	bool match(char expected);
	char peek() const;
	char peek_next() const;

	void add_token(token_type type, std::any literal);
	void add_token(token_type);

	void comment();
	void string();
	void number();
	void identifier();

	void scan_token();

	[[noreturn]] void throw_exception(char const* msg);
};

} // next