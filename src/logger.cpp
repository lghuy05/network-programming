#include "logger.hpp"
#include <iostream>

Logger::Logger(const std::string &name) : name_(name) {};
void Logger::info(const std::string &message) {
  std::cout << name_ << "[" << message << "] " << std::endl;
}
