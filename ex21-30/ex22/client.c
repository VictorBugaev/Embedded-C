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
  udp.len = htons(PAYLOAD_SIZE + sizeof(udp));

  char message[sizeof(udp) + PAYLOAD_SIZE];
  memcpy(message, &udp, sizeof(udp));
  char payload[PAYLOAD_SIZE] = "Hello from client!\n";
  memcpy(message + sizeof(udp), payload, strlen(payload));

  struct sockaddr_in serv;
  int size = sizeof(struct sockaddr_in);

  if (sendto(fd, message, sizeof(message), 0, (struct sockaddr *)&serv, size) ==
      -1) {
    perror("sendto");
    return -1;
  }

  while (1) {
    if (recvfrom(fd, message, sizeof(message), 0, (struct sockaddr *)&serv,
                 &size) == -1) {
      perror("recvto");
      return -1;
    }
    int n = strlen(message); // определение длины строки

    // Удаление первых 28 символов строки
    memmove(message, message + 28, n - 28 + 1);
    printf("%s\n", message);
  }

  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
