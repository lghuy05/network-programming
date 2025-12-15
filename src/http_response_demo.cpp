#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

std::string make_response(const std::string &body, int status = 200) {
  std::string status_text = (status == 200) ? "OK" : "Not Found";
  return "HTTP/1.1 " + std::to_string(status) + " " + status_text +
         "\r\n"
         "Content-Type: text/plain\r\n"
         "Content-Length: " +
         std::to_string(body.size()) +
         "\r\n"
         "\r\n" +
         body;
}

int main() {
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1) {
    perror("socker");
    return 1;
  }

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(listen_fd, (sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("bind");
    close(listen_fd);
    return 1;
  }

  if (listen(listen_fd, 5) == -1) {
    perror("listen");
    close(listen_fd);
    return 1;
  }
  std::cout << "listening from server\n";
  int client_fd = accept(listen_fd, nullptr, nullptr);
  if (client_fd == -1) {
    perror("accept");
    close(listen_fd);
    return 1;
  }

  char buffer[2048];
  ssize_t byte_read = read(client_fd, buffer, sizeof(buffer) - 1);
  if (byte_read > 0) {
    buffer[byte_read] = '\0';
    std::cout << "Request: " << buffer << std::endl;
  }

  std::string request(buffer);
  size_t pos = request.find("\r\n");

  if (pos == std::string::npos) {
    perror("Request");
    close(client_fd);
    close(listen_fd);
    return 1;
  }
  std::string request_header = request.substr(0, pos);
  std::cout << "Request header: " << request_header << std::endl;

  std::istringstream iss(request_header);
  std::string method, path, version;
  iss >> method >> path >> version;
  std::string body;
  int status = 200;

  if (method == "GET" && path == "/") {
    body = "hello from server";
  } else if (method == "GET" && path == "/health") {
    body = "OK";
  } else {
    body = "404 Not Found";
    status = 404;
  }

  std::string response = make_response(body, status);
  // const char *response = "HTTP/1.1 200 OK\r\n"
  //                        "Content-Type: text/plain\r\n"
  //                        "Content_Length: 18\r\n"
  //                        "\r\n"
  //                        "hello from server\n";
  //
  write(client_fd, response.c_str(), response.size());

  close(client_fd);
  close(listen_fd);
  return 0;
}
