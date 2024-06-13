#include "main.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int udp_client() {
  int message_count = 10;
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(UDP_PORT);
  inet_pton(AF_INET, SERVER, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_DGRAM, 0);

  char message[256] = "Helo from UDP client\n";

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  int size = sizeof(struct sockaddr);

  if (sendto(fd, message, sizeof(message), 0, (struct sockaddr *)&addr, size) ==
      -1) {
    perror("sendto");
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
  return 0;
}
int main() { udp_client(); }
