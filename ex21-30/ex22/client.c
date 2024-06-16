#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define DEST_PORT 20000
#define SRC_PORT 20001
#define PAYLOAD_SIZE 248
#define UDP_SIZE 8 
#define HEADER_SIZE 28
#define LEN 256
int main() {
  int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  struct udphdr udp;

  udp.dest = htons(DEST_PORT);
  udp.source = htons(SRC_PORT);
  udp.check = 0;
  udp.len = htons(PAYLOAD_SIZE + UDP_SIZE);

  char message[UDP_SIZE + PAYLOAD_SIZE];
  memcpy(message, &udp, UDP_SIZE);
  char payload[PAYLOAD_SIZE] = "Hello from client!\n";
  memcpy(message + UDP_SIZE, payload, PAYLOAD_SIZE);

  struct sockaddr_in serv;
  int size = sizeof(struct sockaddr_in);

  if (sendto(fd, message, LEN, 0, (struct sockaddr *)&serv, size) ==
      -1) {
    perror("sendto");
    return -1;
  }

  while (1) {
    if (recvfrom(fd, message, LEN, 0, (struct sockaddr *)&serv,
                 &size) == -1) {
      perror("recvto");
      return -1;
    }
    memmove(message, message + HEADER_SIZE, LEN - HEADER_SIZE + 1);
    printf("%s\n", message);
  }

  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
