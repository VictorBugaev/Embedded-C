#include "main.h"
int main_client() {
  pid_t pid = getpid();
  char message[256];
  int message_count = 10;
  int new_fd;
  sprintf(message, "Client pid - %d connected to subserver!\n", pid);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
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
  // sleep(20);
}

void *new_server() {
  char message[256];
  char *new_mes = "You are connect subserver !\n";

  char mqueue_buffer[256];
  char *mq_name = "/mqueue";
  mqd_t mqueue_fd = mq_open(mq_name, O_RDWR);

  if (mqueue_fd == -1) {
    perror("mq_open");
  }

  if (mq_receive(mqueue_fd, mqueue_buffer, sizeof(mqueue_buffer), 0) == -1) {
    perror("mq_receive");
  }

  int server_fd = atoi(mqueue_buffer);

  if (mq_close(mqueue_fd) == -1) {
    perror("mq_close");
  }
  if (mq_unlink(mq_name) == -1) {
    perror("mq_unlink");
  }

  if (recv(server_fd, message, sizeof(message), 0) == -1) {
    perror("recv");
  }

  printf("%s", message);

  memset(message, 0, sizeof(message));
  strncpy(message, new_mes, strlen(new_mes));

  if (send(server_fd, message, sizeof(message), 0) == -1) {
    perror("send");
  }

  pthread_exit(NULL);
}

int main_server() {
  char message[256];
  int message_count = 10;
  int new_fd;

  unlink(SERVER);
  struct sockaddr_in addr, client;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_pton(AF_INET, SERVER, &(addr.sin_addr));

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

  int size = sizeof(struct sockaddr);

  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_curmsgs = 0;
  attr.mq_msgsize = 256;
  while (1) {
    pthread_t id;

    char *mq_name = "/mqueue";
    char mqueue_buffer[256];
    mqd_t mqueue_fd = mq_open(mq_name, O_RDWR | O_CREAT, 0666, &attr);
    if (mqueue_fd == -1) {
      perror("mq_open");
      return -1;
    }

    if ((new_fd = accept(fd, (struct sockaddr *)&client, &size)) == -1) {
      perror("accept");
      return -1;
    }

    sprintf(mqueue_buffer, "%d", new_fd);

    if (mq_send(mqueue_fd, mqueue_buffer, strlen(mqueue_buffer), 0) == -1) {
      perror("mq_send");
      return -1;
    }

    if (mq_close(mqueue_fd) == -1) {
      perror("mq_close");
      return -1;
    }

    if (pthread_create(&id, NULL, new_server, NULL) != 0) {
      perror("pethread_create");
      return -1;
    }

    pthread_join(id, NULL);
  }

  if (close(fd) == -1) {
    perror("close");
    return -1;
  }
}
