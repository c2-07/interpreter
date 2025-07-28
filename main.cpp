#include "Runner.h"
#include <iostream>


int main(int argc, char **argv) {
  if (argc == 2) {
    Runner::runFile(argv[1]);
  } else if (argc == 1) {
    Runner::runPrompt();
  } else {
    std::cout << "Usage: nesx [Script file]";
  }
}