#pragma once
#include <string>

class Logger {
public:
  explicit Logger(const std::string &name);
  void info(const std::string &message);

private:
  std::string name_;
};
