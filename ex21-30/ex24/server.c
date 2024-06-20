#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER "10.20.0.10"
#define PORT 20000

int main() {

  struct sockaddr_in addr, client;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER, &(addr.sin_addr));
  int size = sizeof(struct sockaddr);

  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  char message[256];

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    return -1;
  }

  if (recvfrom(fd, message, sizeof(message), 0, (struct sockaddr *)&client,
               &size) == -1) {
    perror("recv");
    return -1;
  }

  printf("%s\n", message);

  memset(message, 0, sizeof(message));

  strncpy(message, "Hello from server!\n", 20);
  if (sendto(fd, message, sizeof(message), 0, (struct sockaddr *)&client,
             size) == -1) {
    perror("send");
    return -1;
  }

  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
