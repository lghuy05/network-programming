#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    std::cerr << "Failed to create socket\n";
    return 1;
  }
  std::cout << "Socket created, fd = " << fd << std::endl;
  close(fd);
  std::cout << "Socket closed\n";
  return 0;
}
