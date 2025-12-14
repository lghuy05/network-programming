#include "file.hpp"
#include "logger.hpp"
#include <iostream>
#include <unistd.h>

int main() {
  std::cout << "STDIN fd: " << STDIN_FILENO << std::endl;
  std::cout << "STDOUT fd: " << STDOUT_FILENO << std::endl;
  std::cout << "STDERR fd: " << STDERR_FILENO << std::endl;
}
