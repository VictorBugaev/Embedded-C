#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int message_count = 10;
  int new_fd;
  struct sockaddr addr = {AF_LOCAL, "Server"}, client;
  int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
  char message[256];
  if (fd == -1) {
    perror("socket");
    return -1;
  }
  printf("fd - %d\n", fd);

  if (bind(fd, &addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    return -1;
  }

  if (listen(fd, message_count) == -1) {
    perror("listen");
    return -1;
  }
  int size = sizeof(struct sockaddr);
  new_fd = accept(fd, &addr, &size);

  if (new_fd == -1) {
    perror("accept");
    return -1;
  }
  printf("new_fd - %d\n", fd);

  if (recv(new_fd, message, sizeof(message), 0) == -1) {
    perror("recv");
    return -1;
  }

  printf("%s", message);

  memset(message, 0, sizeof(message));

  strncpy(message, "Hello from server\n", 20);

  if (send(new_fd, message, sizeof(message), 0) == -1) {
    perror("send");
    return -1;
  }

  if ((close(new_fd) | close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
