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
  int size = sizeof(struct sockaddr);

  int fd = socket(AF_INET, SOCK_DGRAM, 0);

  char message[256] = "Hello from server\n";

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  // int flag = 1;
  // if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) == -1) {
  //   perror("setsockopt");
  //   return -1;
  // }

  while (1) {
    if (sendto(fd, message, sizeof(message), 0, (struct sockaddr *)&addr,
               size) == -1) {
      perror("send");
      return -1;
    }
  }
  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
