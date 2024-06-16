#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define DEST_PORT 20000
#define SRC_PORT 20001
#define SERVER "127.0.0.1"
#define LEN 256
#define IP_LEN 20
#define UDP_LEN 8
#define HEADER_LEN 28
#define PAYLOAD_SIZE 228

int main() {
  int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  int flag = 1;
  setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag));

  if (fd == -1) {
    perror("socket");
    return -1;
  }
  struct iphdr ip;

  ip.check = 0;
  inet_pton(AF_INET, SERVER, &(ip.daddr));
  ip.frag_off = 0;
  ip.id = 0;
  ip.ihl = 5;
  ip.protocol = 17;
  ip.saddr = 0;
  ip.tos = 0;
  ip.tot_len = LEN;
  ip.ttl = 100;
  ip.version = 4;

  struct udphdr udp;

  udp.dest = htons(DEST_PORT);
  udp.source = htons(SRC_PORT);
  udp.check = 0;
  udp.len = htons(PAYLOAD_SIZE + sizeof(udp));

  char message[LEN];
  memcpy(message, &ip, IP_LEN);
  memcpy(message + IP_LEN, &udp, UDP_LEN);
  char payload[PAYLOAD_SIZE] = "Hello from client!\n";
  memcpy(message + IP_LEN + UDP_LEN, payload, PAYLOAD_SIZE);

  struct sockaddr_in serv;
  int size = sizeof(struct sockaddr_in);

  if (sendto(fd, message, LEN, 0, (struct sockaddr *)&serv, size) == -1) {
    perror("sendto");
    return -1;
  }

  while (1) {
    if (recvfrom(fd, message, LEN, 0, (struct sockaddr *)&serv, &size) == -1) {
      perror("recvto");
      return -1;
    }
    memmove(message, message + HEADER_LEN, LEN - HEADER_LEN + 1);
    printf("%s\n", message);
  }

  if ((close(fd)) == -1) {
    perror("close");
    return -1;
  }
}
