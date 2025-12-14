#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    std::cerr << "socket() failed\n";
    return 1;
  }
  sockaddr_in addr;
  std::memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (sockaddr *)&addr, sizeof(addr)) == -1) {
    std::cerr << "bind() failed\n";
    close(fd);
    return 1;
  }
  std::cout << "Socket bound to port 8080\n";
  close(fd);
  return 0;
}
