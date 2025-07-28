#ifndef RUNNER_H
#define RUNNER_H

#include "Token.h"
#include <string>

class Runner {
public:
  static void runFile(const std::string &path);
  static void runPrompt();
  static void error(int line, const std::string& message);

private:
  static void run(const std::string &source);
  static void report(int line, const std::string& where, const std::string& message);

private:
  static bool hadError;
  static bool hadRuntimeError;
};

#endif // NESXRUNNER_H
