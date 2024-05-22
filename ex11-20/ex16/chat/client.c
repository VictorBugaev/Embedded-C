#include "main.h"
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int client_exit(mqd_t fd) {
  char exit_message[256] = "exit";
  printf("You a leaved the chat");
  if (mq_send(fd, exit_message, strlen(exit_message), 1) == -1) {
    perror("mq_send");
    return (-1);
  }
}
int main() {
  pid_t pid = getpid();
  printf("My pid %d\n", pid);
  char *client = "/client_queue";
  char *server = "/server_queue";
  mqd_t client_fd;
  mqd_t server_fd;

  client_fd = mq_open(client, O_RDWR, 0666);
  server_fd = mq_open(server, O_RDWR, 0666);

  if (server_fd == -1) {
    perror("serv - mq_open");
    return (-1);
  }
  if (client_fd == -1) {
    perror("cl - mq_open");
    return (-1);
  }
  client_connection_to_server(server_fd, pid);
  int f = 1;
  while (f) {
    f = client_message_to_server(client_fd, pid, f);
  }
  client_exit(client_fd);
  if (mq_close(client_fd) == -1) {
    perror("mq_close");
    return (-1);
  }
  if (mq_close(server_fd) == -1) {
    perror("mq_close");
    return (-1);
  }
  return 0;
}