#include "scanner.h"

namespace next {

[[noreturn]] void scanner::throw_exception(char const* msg) {
	std::stringstream ss;
	ss << "line " << m_line << ": " << msg;
	throw std::runtime_error(ss.str());
}

std::vector<token> scanner::scan_tokens() {
	while (!is_at_end()) {
		m_start = m_current;
		scan_token();
	}
	m_tokens.emplace_back(token_type::Eof, "", m_line);
	return m_tokens;
}

bool scanner::is_at_end() const {
	return m_current >= static_cast<int>(m_src.length());
}

char scanner::advance() {
	++m_current;
	return m_src.at(m_current - 1);
}

void scanner::add_token(token_type type, std::any literal) {
	m_tokens.emplace_back(type, m_src.substr(m_start, m_current - m_start), literal, m_line);
}

void scanner::add_token(token_type type) {
	add_token(type, std::any{});
}

bool scanner::match(char expected) {
	if (is_at_end() || m_src.at(m_current) != expected)
		return false;
	++m_current;
	return true;
}

char scanner::peek() const {
	if (is_at_end())
		return '\0';
	return m_src.at(m_current);
}

char scanner::peek_next() const {
	if (m_current + 1 >= static_cast<int>(m_src.length()))
		return '\0';
	return m_src.at(m_current + 1);
}

void scanner::comment() {
	while (peek() != '\n' && !is_at_end())
		advance();
}

void scanner::string() {
	while (peek() != '"' && is_at_end()) {
		if (peek() == '\n')
			++m_line;
		advance();
	}
	if (is_at_end())
		throw_exception("[Error] unterminated string.");
	advance();
	add_token(token_type::String, m_src.substr(m_start + 1, m_current - m_start - 2));
}

void scanner::number() {
	while (std::isdigit(peek()))
		advance();
	if (peek() == '.' && std::isdigit(peek_next())) {
		advance();
		while (std::isdigit(peek()))
			advance();
	}
	add_token(token_type::Number, std::stod(m_src.substr(m_start, m_current - m_start)));
}

void scanner::identifier() {
	while (std::isdigit(peek()) || std::isalpha(peek()) || peek() == '_')
		advance();
	const auto text = m_src.substr(m_start, m_current - m_start);
	if (const auto it = m_keywords.find(text); it != m_keywords.end())
		add_token(it->second);
	else
		add_token(token_type::Identifier);
}

void scanner::scan_token() {
	char c = advance();
	switch (c) {
	case '(':
		add_token(token_type::LeftParen);
		break;
	case ')':
		add_token(token_type::RightParen);
		break;
	case '{':
		add_token(token_type::LeftBrace);
		break;
	case '}':
		add_token(token_type::RightBrace);
		break;
	case ',':
		add_token(token_type::Comma);
		break;
	case '.':
		add_token(token_type::Dot);
		break;
	case '-':
		add_token(token_type::Minus);
		break;
	case '+':
		add_token(token_type::Plus);
		break;
	case ';':
		add_token(token_type::Semicolon);
		break;
	case '*':
		add_token(token_type::Star);
		break;
	case '!':
		add_token(match('=') ? token_type::BangEqual : token_type::Bang);
		break;
	case '=':
		add_token(match('=') ? token_type::EqualEqual : token_type::Equal);
		break;
	case '<':
		add_token(match('=') ? token_type::LessEqual : token_type::Less);
		break;
	case '>':
		add_token(match('=') ? token_type::GreaterEqual : token_type::Greater);
		break;
	case '/':
		if (!match('/'))
			add_token(token_type::Slash);
		else
			comment();
		break;
	case ' ':
	case '\r':
	case '\t':
		break;
	case '\n':
		++m_line;
		break;
	case '"':
		string();
		break;
	default:
		if (std::isdigit(c))
			number();
		else if (std::isalpha(c) || c == '_')
			identifier();
		else
			throw_exception("[Error] unexpected character.");
		break;
	}
}

} // next