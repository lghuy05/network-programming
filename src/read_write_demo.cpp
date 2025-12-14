#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1) {
    perror("socket");
    return 1;
  }
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(listen_fd, (sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Bind");
    close(listen_fd);
    return 1;
  }
  if (listen(listen_fd, 5) == -1) {
    perror("Listen");
    close(listen_fd);

    return 1;
  }

  int client_fd = accept(listen_fd, nullptr, nullptr);
  if (client_fd == -1) {
    perror("accept");
    close(listen_fd);
    return 1;
  }

  char buffer[1024];
  ssize_t byte_read = read(client_fd, buffer, sizeof(buffer) - 1);
  if (byte_read > 0) {
    buffer[byte_read] = '\0';
    std::cout << "Received:\n" << buffer << std::endl;
  }
  const char *response = "hello fromn server\n";
  write(client_fd, response, strlen(response));
  close(client_fd);
  close(listen_fd);
  return 0;
}
