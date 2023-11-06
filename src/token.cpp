#include "token.h"

namespace next {

[[maybe_unused]] std::string token::to_string() const {
	return "type: " + std::to_string(static_cast<int>(m_type)) +
		"\nlexeme: " + m_lexeme +
		"\nliteral: " + literal_to_string();
}

[[maybe_unused]] std::string token::literal_to_string() const {
	switch (m_type) {
	case token_type::String:
		return std::any_cast<std::string>(m_literal);
	case token_type::Number:
		return std::to_string(std::any_cast<double>(m_literal));
	}
	return "";
}

} // next