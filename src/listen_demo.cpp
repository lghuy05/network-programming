#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1) {
    std::cerr << "Socket failed\n";
    return 1;
  }
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(listen_fd, (sockaddr *)&addr, sizeof(addr)) == 1) {
    std::cerr << "bind failed\n";
    close(listen_fd);
    return 1;
  }

  if (listen(listen_fd, 5) == -1) {
    std::cerr << "listen failed\n";
    close(listen_fd);
    return 1;
  }
  std::cout << "Server is listening on port 8080...\n";

  int client_fd = accept(listen_fd, nullptr, nullptr);
  if (client_fd == -1) {
    std::cerr << "Accept failed\n";
    return 1;
  }
  std::cout << "Client connected\n";
  close(listen_fd);
  close(client_fd);
  return 0;
}
