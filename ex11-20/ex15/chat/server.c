#include "main.h"
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
  char *client = "/client_queue";
  char *server = "/server_queue";
  mqd_t client_fd;
  mqd_t server_fd;
  int f = 1;

  struct mq_attr attr;
  attr.mq_flags = 0; // O_NONBLOCK;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 256;
  attr.mq_curmsgs = 0;
  client_fd = mq_open(client, O_CREAT | O_RDWR | O_NONBLOCK, 0666, &attr);
  server_fd = mq_open(server, O_CREAT | O_RDWR, 0666, &attr);
  if (server_fd == -1) {
    perror("serv - mq_open");
    return (-1);
  }
  if (client_fd == -1) {
    perror("cl - mq_open");
    return (-1);
  }

  while (f) {
    server_connection(server_fd, attr);
    server_catch_messages(client_fd, attr);
  }

  if (mq_close(server_fd) == -1) {
    perror("mq_close");
    return (-1);
  }
  if (mq_close(client_fd) == -1) {
    perror("mq_close");
    return (-1);
  }
  if (mq_unlink(server) == -1) {
    perror("mq_unlink");
    return (-1);
  }
  if (mq_unlink(client) == -1) {
    perror("mq_unlink");
    return (-1);
  }
  return 0;
}