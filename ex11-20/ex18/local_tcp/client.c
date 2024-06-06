#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char message[256] = "Hello from client\n";
  int message_count = 10;
  struct sockaddr addr = {AF_LOCAL, "Server"};
  int fd = socket(AF_LOCAL, SOCK_STREAM, 0);

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  connect(fd, &addr, sizeof(struct sockaddr));

  if (fd == -1) {
    perror("accept");
    return -1;
  }
  printf("fd - %d\n", fd);
  if (send(fd, message, sizeof(message), 0) == -1) {
    perror("send");
    return -1;
  }

  memset(message, 0, strlen(message));

  if (recv(fd, message, sizeof(message), 0) == -1) {
    perror("recv");
    return -1;
  }

  printf("%s", message);

  if (close(fd) == -1) {
    perror("close");
    return -1;
  }
}
