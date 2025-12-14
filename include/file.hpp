#pragma once
#include <string>

class File {
public:
  explicit File(const std::string &path);
  ~File();
  void write(const std::string &text);
  void fd_info();

private:
  int fd_;
};
