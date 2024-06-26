#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 2000
#define SERVER "Server"

int main() {
  char message[256] = "Hello from client\n";
  int message_count = 10;
  int new_fd;

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  printf("fd - %d\n", fd);

  int size = sizeof(struct sockaddr);
  connect(fd, (struct sockaddr *)&addr, size);

  if (send(fd, message, sizeof(message), 0) == -1) {
    perror("send");
    return -1;
  }

  memset(message, 0, sizeof(message));

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
