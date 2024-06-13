#include "main.h"

int main_function() {
  char *new_mes = "Hello from server\n";
  char message[MESSAGE_SIZE];

  struct sockaddr_in tcp_addr;
  int tcp_addrlen = sizeof(tcp_addr);
  int tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_fd == -1) {
    perror("socket");
    return -1;
  }
  tcp_addr.sin_family = AF_INET;
  tcp_addr.sin_port = htons(TCP_PORT);
  tcp_addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(tcp_addr.sin_addr));

  if (bind(tcp_fd, (struct sockaddr *)&tcp_addr, tcp_addrlen) == -1) {
    perror("tcp bind");
    return -1;
  }
  if (listen(tcp_fd, MESSAGE_COUNT) == -1) {
    perror("listen");
    return -1;
  }

  struct sockaddr_in udp_addr;
  int udp_addrlen = sizeof(udp_addr);
  int udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (udp_fd == -1) {
    perror("socket");
    return -1;
  }
  udp_addr.sin_family = AF_INET;
  udp_addr.sin_port = htons(UDP_PORT);
  udp_addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(udp_addr.sin_addr));
  if (bind(udp_fd, (struct sockaddr *)&udp_addr, udp_addrlen) == -1) {
    perror("udp bind");
    return -1;
  }

  int epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    perror("epoll_create1");
    return -1;
  }
  struct epoll_event event;
  event.events = EPOLLIN;

  event.data.fd = tcp_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tcp_fd, &event) == -1) {
    perror("epoll_ctl");
    return -1;
  }

  event.data.fd = udp_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, udp_fd, &event) == -1) {
    perror("epoll_ctl");
    return -1;
  }
  struct epoll_event events[MAX_EVENTS];
  while (1) {
    int count_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    for (int i = 0; i < count_events; i++) {
      int fd = events[i].data.fd;
      if (fd == tcp_fd) {
        int new_fd = accept(fd, (struct sockaddr *)&tcp_addr, &tcp_addrlen);
        if (new_fd == -1) {
          perror("accept");
          return -1;
        }
        if (recv(new_fd, message, MESSAGE_SIZE, 0) == -1) {
          perror("recv");
          return -1;
        }
        printf("%s", message);
        memset(message, 0, MESSAGE_SIZE);
        sprintf(message, "%s", new_mes);
        if (send(new_fd, message, strlen(message), 0) == -1) {
          perror("send");
          return -1;
        }
      } else if (fd == udp_fd) {
        if (recvfrom(fd, message, MESSAGE_SIZE, 0, (struct sockaddr *)&udp_addr,
                     &udp_addrlen) == -1) {
          perror("recvfrom");
          return -1;
        }
        printf("%s", message);
        memset(message, 0, MESSAGE_SIZE);
        sprintf(message, "%s", new_mes);
        if (sendto(fd, message, MESSAGE_SIZE, 0, (struct sockaddr *)&udp_addr,
                   udp_addrlen) == -1) {
          perror("sendto");
          return -1;
        }
      } else {
        printf("Unknown fd\n");
      }
    }
  }
  return 0;
}

int tcp_client() {
  char message[256] = "Hello from TCP client\n";
  int message_count = 10;
  int new_fd;

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(TCP_PORT);
  addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  int size = sizeof(struct sockaddr);
  connect(fd, (struct sockaddr *)&addr, size);

  if (send(fd, message, sizeof(message), 0) == -1) {
    perror("send");
    return -1;
  }

  memset(message, 0, sizeof(message));

  if (recv(fd, message, sizeof(message), 0) == -1) {
    perror("recv");
    return -1;
  }
  printf("%s", message);

  if (close(fd) == -1) {
    perror("close");
    return -1;
  }
  return 0;
}