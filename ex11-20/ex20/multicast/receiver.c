#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER "224.0.0.1"
#define PORT 7777

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

  struct ip_mreqn multicast;
  inet_pton(AF_INET, SERVER, &(multicast.imr_multiaddr));
  multicast.imr_address.s_addr = INADDR_ANY;
  int imr_ifindex = 0;

  if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast,
                 sizeof(multicast)) == -1) {
    perror("setsockopt");
    return -1;
  }

  int size = sizeof(struct sockaddr);

  if (bind(fd, (struct sockaddr *)&addr, size) == -1) {
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
