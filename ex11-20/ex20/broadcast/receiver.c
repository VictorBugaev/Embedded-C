#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER "255.255.255.255"
#define PORT 2000

int main() {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_DGRAM, 0);

  char message[256];

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  int size = sizeof(struct sockaddr);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    return -1;
  }

  if (recvfrom(fd, message, sizeof(message), 0, (struct sockaddr *)&addr,
               &size) == -1) {
    perror("recvto");
    return -1;
  }

  printf("%s", message);

  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
