#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define PORT 2000

int main() {
  int message_count = 10;

  struct sockaddr_in addr, client;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER, &(addr.sin_addr));
  int size = sizeof(struct sockaddr);

  int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

  char message[256];

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  printf("fd - %d\n", fd);
  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    return -1;
  }
  while(1){
    if (recvfrom(fd, message, sizeof(message), 0, (struct sockaddr *)&client, &size) == -1) {
      perror("recv");
      return -1;
    }
    printf("%s\n", message);
    printf("Пакет получен\n");
    
    memset(message, 0, strlen(message));
  }
  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
