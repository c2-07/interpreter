#include "Token.h"
#include <any>
#include <sstream>
#include <string>

Token::Token(TokenType type,const std::string &lexeme, std::any literal, const int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::toString() {
  std::ostringstream out; // <- ????? and Also Wtf <int> for?
  out << static_cast<int>(type) << " " << lexeme << " ";

  if (literal.has_value()) {
    try {
      if (literal.type() == typeid(std::string))
        out << std::any_cast<std::string>(literal);

      else if (literal.type() == typeid(double))
        out << std::any_cast<double>(literal);

      else if (literal.type() == typeid(int))
        out << std::any_cast<int>(literal);

      else
        out << "[Unknown literal type]";

    } catch (const std::bad_any_cast) {
      out << "[Bad any cast]";
    }
  } else {
    out << "nil";
  }
  return out.str();
}