#include "main.h"

int server_connection(mqd_t fd, struct mq_attr attr) {
  char server_message[256];
  if (mq_receive(fd, server_message, sizeof(server_message), NULL) == -1) {
    if (errno != EAGAIN) {
      perror("server mq_receive");
      return -1;
    }
  } else {
    printf("%s\n", server_message);
    memset(server_message, 0, strlen(server_message));
    char *message = "You connected to the server! Write your message\n";
    strncpy(server_message, message, strlen(message));
    if (mq_send(fd, server_message, strlen(server_message), 1) == -1) {
      perror("mq_send");
    }
    memset(server_message, 0, strlen(server_message));
    if (attr.mq_flags != O_NONBLOCK) {
      attr.mq_flags = O_NONBLOCK;
      if (mq_setattr(fd, &attr, NULL)) {
        perror("mq_setattr");
        return -1;
      }
    }
  }
  return 0;
}

int server_catch_messages(mqd_t fd, struct mq_attr attr) {
  char client_message[256];

  if (mq_receive(fd, client_message, sizeof(client_message), 0) == -1 &&
      errno != EAGAIN) {
    perror("client mq_receive");
  }
  if (strcmp(client_message, "exit") == 0) {
    printf("Client leave the chat\n");
  } else if (strlen(client_message)) {
    printf("%s\n", client_message);
  }
  memset(client_message, 0, strlen(client_message));
}