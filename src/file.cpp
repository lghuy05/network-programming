#include "file.hpp"
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

File::File(const std::string &path)
    : fd_(open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644)) {
  if (fd_ == -1) {
    throw std::runtime_error("Failed to open file");
  }
}

File::~File() {
  if (fd_ != -1) {
    close(fd_);
  }
}

void File::write(const std::string &text) {
  ::write(fd_, text.c_str(), text.size());
}

void File::fd_info() { std::cout << fd_ << std::endl; }
