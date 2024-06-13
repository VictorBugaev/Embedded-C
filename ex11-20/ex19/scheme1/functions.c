#include "main.h"
int tcp_client() {
  pid_t pid = getpid();
  char message[256];
  int message_count = 10;
  int new_fd;
  sprintf(message, "Client pid - %d\n", pid);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  printf("fd - %d\n", fd);

  int size = sizeof(struct sockaddr);
  connect(fd, (struct sockaddr *)&addr, size);
  int f = 1;
  while (f) {
    fgets(message, sizeof(message), stdin);
    if (strcmp("exit\n", message) == 0) {
      if (close(fd) == -1) {
        perror("close");
        return -1;
      }
      f = 0;
    } else {
      if (send(fd, message, sizeof(message), 0) == -1) {
        perror("send");
        return -1;
      }

      if (recv(fd, message, sizeof(message), 0) == -1) {
        perror("recv");
        return -1;
      }
      printf("%s", message);
    } // sleep(30);
  }
  return 0;
}

int main_server() {
  char message[256];
  int message_count = 10;
  int new_fd;

  struct sockaddr_in addr, client;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(addr.sin_addr));

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  printf("fd - %d\n", fd);

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
    pthread_t id;
    if ((new_fd = accept(fd, (struct sockaddr *)&client, &size)) == -1) {
      perror("accept");
      return -1;
    }
    if (pthread_create(&id, NULL, new_server, (void *)&new_fd) != 0) {
      perror("pethread_create");
      return -1;
    }
    pthread_join(id, NULL);
  }

  if (close(fd) == -1) {
    perror("close");
    return -1;
  }
  return 0;
}
void *new_server(void *args) {
  char message[256];
  char *new_mes = "You are connect server\n";
  int *fd = (int *)args;
  printf("new_fd - %d\n", *fd);
  if (recv(*fd, message, sizeof(message), 0) == -1) {
    perror("recv");
  }
  printf("%s", message);
  memset(message, 0, sizeof(message));
  strncpy(message, new_mes, strlen(new_mes));

  if (send(*fd, message, sizeof(message), 0) == -1) {
    perror("send");
  }

  pthread_exit(NULL);
}
