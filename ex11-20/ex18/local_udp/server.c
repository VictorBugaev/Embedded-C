#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int message_count = 10;
  struct sockaddr addr = {AF_LOCAL, "Server"}, client;
  int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
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
  int size = sizeof(struct sockaddr);
  if (recvfrom(fd, message, sizeof(message), 0, &client, &size) == -1) {
    perror("recv");
    return -1;
  }

  printf("%s", message);

  memset(message, 0, sizeof(message));

  strncpy(message, "Hello from server\n", 20);

  if (sendto(fd, message, sizeof(message), 0, &client, &size) == -1) {
    perror("send");
    return -1;
  }

  if ((close(new_fd) | close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
