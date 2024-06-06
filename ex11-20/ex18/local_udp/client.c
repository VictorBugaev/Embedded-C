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

  int size = sizeof(struct sockaddr);
  
  if (sendto(fd, message, sizeof(message), 0, &client, &size) == -1) {
    perror("send");
    return -1;
  }

  memset(message, 0, sizeof(message));

  strncpy(message, "Hello from client\n", 20);

  if (recvfrom(fd, message, sizeof(message), 0, &client, &size) == -1) {
    perror("recv");
    return -1;
  }

  printf("%s", message);

  if (close(fd) == -1) {
    perror("close");
    return -1;
  }
}
