#include "Scanner.h"
#include "Runner.h" // for Runner::error
#include "Token.h"

const std::unordered_map<std::string, TokenType> Scanner::keywords = {
    {"and", TokenType::AND},       {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
    {"for", TokenType::FOR},       {"fun", TokenType::FUN},
    {"if", TokenType::IF},         {"nil", TokenType::NIL},
    {"or", TokenType::OR},         {"print", TokenType::PRINT},
    {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
    {"this", TokenType::THIS},     {"true", TokenType::TRUE},
    {"var", TokenType::VAR},       {"while", TokenType::WHILE}};

Scanner::Scanner(const std::string &src) : source(src) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  tokens.emplace_back(TokenType::EOF_TOKEN, "", nullptr, line);
  return tokens;
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case '.':
    addToken(TokenType::DOT);
    break;
  case '-':
    addToken(TokenType::MINUS);
    break;
  case '+':
    addToken(TokenType::PLUS);
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    break;
  case '*':
    addToken(TokenType::STAR);
    break;

  case '!':
    addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;

  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd())
        advance();
    } else {
      addToken(TokenType::SLASH);
    }
    break;

  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    stringLiteral();
    break;

  default:
    if (isDigit(c)) {
      number();
    } else if (isAlpha(c)) {
      identifier();
    } else {
      Runner::error(line, "Unexpected character.");
    }
    break;
  }
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek()))
    advance();
  std::string text = source.substr(start, current - start);
  auto it = keywords.find(text);
  TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
  addToken(type);
}

void Scanner::number() {
  while (isDigit(peek()))
    advance();
  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek()))
      advance();
  }
  double value = std::stod(source.substr(start, current - start));
  addToken(TokenType::NUMBER, value);
}

void Scanner::stringLiteral() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (isAtEnd()) {
    Runner::error(line, "Unterminated string.");
    return;
  }

  advance(); // closing quote
  std::string value = source.substr(start + 1, current - start - 2);
  addToken(TokenType::STRING, value);
}

bool Scanner::match(char expected) {
  if (isAtEnd())
    return false;
  if (source[current] != expected)
    return false;
  current++;
  return true;
}

char Scanner::peek() { return isAtEnd() ? '\0' : source[current]; }

char Scanner::peekNext() {
  return (current + 1 >= source.size()) ? '\0' : source[current + 1];
}

bool Scanner::isAlpha(char c) const {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) const { return isAlpha(c) || isDigit(c); }

bool Scanner::isDigit(char c) const { return c >= '0' && c <= '9'; }

bool Scanner::isAtEnd() const { return current >= source.length(); }

char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source.substr(start, current - start);
  tokens.emplace_back(type, text, literal, line);
}
