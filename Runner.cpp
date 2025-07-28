#include "Runner.h"
#include "Scanner.h"
#include "Token.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool Runner::hadError = false;
bool Runner::hadRuntimeError = false;

void Runner::runFile(const std::string& path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Couldn't open: " << path << '\n';
    std::exit(74);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  run(buffer.str());

  if (hadError) std::exit(65);
  if (hadRuntimeError) std::exit(70);
}

void Runner::runPrompt() {
  std::string line;

  try {
    while (true) {
      std::cout << ">>> ";
      if (!std::getline(std::cin, line)) break;
      run(line);
      hadError = false; // Reset after each line
    }
  } catch (...) {
    std::exit(0); // Exit silently on fatal input
  }
}

void Runner::run(const std::string& source) {
  // TODO: Scanner, Parser, Interpreter go here
  std::cout << "[debug] received source: " << source << '\n';
  Scanner *scanner = new Scanner(source);
  std::vector<Token> tokens = scanner->scanTokens();
}

void Runner::error(int line, const std::string &message) {
  report(line, "", message);
}

void Runner::report(int line, const std::string& where, const std::string& message) {
  std::cout << line << " | Error " + where + " : " + message;
  hadError = true;
}