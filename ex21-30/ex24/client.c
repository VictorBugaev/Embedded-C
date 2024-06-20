#include <arpa/inet.h>
#include <errno.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define DEST_PORT 20000
#define SRC_PORT 20000
#define SERVER "10.20.0.10"
#define LEN 256
#define IP_LEN 20
#define UDP_LEN 8
#define HEADER_LEN 28
#define PAYLOAD_SIZE 214
#define ETH_LEN 14
#define MAC_DST "08:00:27:D2:A3:B9"
#define MAC_SRC "08:00:27:71:11:46"

void mac_convert(char *str_mac, char *mac) {
  for (int i = 0; i < 18; i += 3) {
    sscanf(str_mac + i, "%2hhx", mac + (i / 3));
  }
}

short check_sum_ip(void *args, int N) {
  int i_cksm = 0;
  unsigned short *ptr = (unsigned short *)args;
  for (int i = 0; i < N; ++i) {
    i_cksm += *ptr;
    ptr++;
  }
  unsigned short cksm =
      (unsigned short)(i_cksm & 0xFFFF) + (unsigned short)(i_cksm >> 16);
  cksm = (unsigned short)(i_cksm & 0xFFFF) + (unsigned short)(i_cksm >> 16);
  return cksm;
}
int main() {

  char *uncorverted_src_mac = MAC_SRC;
  char converted_src_mac[6];

  char *uncorverted_dst_mac = MAC_DST;
  char converted_dst_mac[6];

  mac_convert(uncorverted_src_mac, converted_src_mac);
  mac_convert(uncorverted_dst_mac, converted_dst_mac);

  int fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  if (fd == -1) {
    perror("socket");
    return -1;
  }

  struct sockaddr_ll addr_ll;
  addr_ll.sll_family = AF_PACKET;
  addr_ll.sll_ifindex = if_nametoindex("enp0s3");
  addr_ll.sll_halen = 6;
  addr_ll.sll_hatype = 0;
  addr_ll.sll_pkttype = 0;
  addr_ll.sll_protocol = htons(ETH_P_ALL);

  memcpy(addr_ll.sll_addr, converted_src_mac, sizeof(converted_src_mac));

  struct ethhdr eth;
  memcpy(eth.h_source, converted_src_mac, sizeof(converted_src_mac));
  memcpy(eth.h_dest, converted_dst_mac, sizeof(converted_dst_mac));
  eth.h_proto = htons(ETH_P_IP);

  struct iphdr ip;
  inet_pton(AF_INET, SERVER, &(ip.daddr));
  inet_pton(AF_INET, "10.20.0.20", &(ip.saddr));
  ip.frag_off = 0;
  ip.id = 0;
  ip.ihl = 5;
  ip.protocol = 17;
  ip.tos = 0;
  ip.tot_len = htons(IP_LEN + UDP_LEN + PAYLOAD_SIZE);
  ip.ttl = 100;
  ip.version = 4;

  ip.check = 0;
  ip.check = ~check_sum_ip(&ip, IP_LEN / 2);
  printf("%d\n", ip.check);

  char buf[128];
  printf("size %ld\n", sizeof(ip));
  memcpy(buf, &ip, sizeof(ip));
  int j = strlen(buf);
  printf("strlen %d\n", j);

  struct udphdr udp;
  udp.dest = htons(DEST_PORT);
  udp.source = htons(SRC_PORT);
  udp.len = htons(PAYLOAD_SIZE + sizeof(udp));
  udp.check = 0;

  char message[LEN];
  char payload[PAYLOAD_SIZE] = "Hello from client!\n";

  memcpy(message, &eth, ETH_LEN);
  memcpy(message + ETH_LEN, &ip, IP_LEN);
  memcpy(message + ETH_LEN + IP_LEN, &udp, UDP_LEN);
  memcpy(message + ETH_LEN + IP_LEN + UDP_LEN, payload, strlen(payload));

  while (1) {
    if (sendto(fd, message, LEN, 0, (struct sockaddr *)&addr_ll,
               sizeof(addr_ll)) == -1) {
      perror("sendto");
      return -1;
    }
    if (recvfrom(fd, message, LEN, 0, NULL, NULL) == -1) {
      perror("recvto");
      return -1;
    }
    memmove(message, message + HEADER_LEN + 14, LEN - (HEADER_LEN + 14) + 1);
    printf("%s\n", message);
  }
}
