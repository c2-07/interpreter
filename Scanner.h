#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include "TokenType.h"
#include <any>
#include <string>
#include <unordered_map>
#include <vector>

class Scanner {
public:
  explicit Scanner(const std::string &source);
  std::vector<Token> scanTokens();

private:
  char peek();
  char peekNext();
  char advance();
  bool match(char expected);
  bool isAtEnd() const;
  bool isDigit(char c) const;
  bool isAlpha(char c) const;
  bool isAlphaNumeric(char c) const;
  void number();
  void scanToken();
  void identifier();
  void stringLiteral();
  void addToken(TokenType type, std::any literal = nullptr);

private:
  int start = 0;
  int current = 0;
  int line = 1;
  std::string source;
  std::vector<Token> tokens;
  static const std::unordered_map<std::string, TokenType> keywords;
};

#endif