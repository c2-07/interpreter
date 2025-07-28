#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <any>
#include <string>

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const std::any literal;
  const int line;
  Token(TokenType type, const std::string &lexeme, std::any literal, const int line);
  std::string toString();
};
#endif