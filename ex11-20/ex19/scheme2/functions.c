#include "main.h"

int create_pull(int port) {
  int message_count = 10;
  struct sockaddr_in addr, client;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_pton(AF_INET, ADDRESS, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    return -1;
  }

  if (listen(fd, message_count) == -1) {
    perror("listen");
    return -1;
  }

  return fd;
}

void *connection_to_subserver(void *arg) {
  char message[256];
  int message_count = 1;
  int new_fd;
  struct sub_server *serv = (struct sub_server *)arg;
  struct sockaddr_in addr, client;

  int size = sizeof(struct sockaddr);

  if ((new_fd = accept(serv->fd, (struct sockaddr *)&client, &size)) == -1) {
    perror("accept");
  }

  serv->availible = 0;
  if (recv(new_fd, message, MESSAGE_SIZE, 0) == -1) {
    perror("recv");
  }
  printf("%s", message);

  memset(message, 0, MESSAGE_SIZE);
  sprintf(message, "You are connected to subserver %d...\n", serv->count);

  if (send(new_fd, message, MESSAGE_SIZE, 0) == -1) {
    perror("send");
  }
  serv->availible = 1;

  if (close(new_fd) == -1) {
    perror("close");
  }
  pthread_exit(NULL);
}

int create_main_server(struct sub_server *mass) {
  int message_count = 5;
  int new_fd;

  struct sockaddr_in addr, client;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(MAIN_PORT);
  addr.sin_addr.s_addr = inet_pton(AF_INET, ADDRESS, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  int optval = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror("setsockopt");
    return -1;
  }

  printf("Main server fd - %d\n", fd);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    return -1;
  }

  if (listen(fd, message_count) == -1) {
    perror("listen");
    return -1;
  }

  int size = sizeof(struct sockaddr);

  while (1) {
    if ((new_fd = accept(fd, (struct sockaddr *)&client, &size)) == -1) {
      perror("main accept");
      return -1;
    }
    char message[256];
    if (recv(new_fd, message, MESSAGE_SIZE, 0) == -1) {
      perror("recv");
    }
    printf("%s", message);
    for (int i = 0; i < SERVER_COUNT; i++) {
      if (mass[i].availible == 1) {
        memset(message, 0, MESSAGE_SIZE);
        sprintf(message, "%d\n", mass[i].port);
        if (send(new_fd, message, MESSAGE_SIZE, 0) == -1) {
          perror("send");
        }
        pthread_t id;
        if (pthread_create(&id, NULL, connection_to_subserver,
                           (void *)&mass[i]) != 0) {
          perror("pethread_create");
          return -1;
        }
        pthread_join(id, NULL);
        i = SERVER_COUNT;
      }
    }
  }

  if (close(new_fd) | close(fd) == -1) {
    perror("close");
    return -1;
  }
  return 0;
}

int create_a_client(int port, char *message) {
  int message_count = 10;

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_pton(AF_INET, ADDRESS, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  int optval = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror("setsockopt");
    return -1;
  }

  int size = sizeof(struct sockaddr);

  connect(fd, (struct sockaddr *)&addr, size);

  if (send(fd, message, MESSAGE_SIZE, 0) == -1) {
    perror("send");
    return -1;
  }

  if (recv(fd, message, MESSAGE_SIZE, 0) == -1) {
    perror("recv");
    return -1;
  }

  printf("%s", message);

  if (close(fd) == -1) {
    perror("close");
    return -1;
  }

  int new_port = atoi(message);
  return new_port;
}
