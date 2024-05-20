#include "main.h"

int client_connection_to_server(mqd_t fd, pid_t pid) {
  char connection_message[256];
  sprintf(connection_message, "Client %d connected to server\n", pid);
  if (mq_send(fd, connection_message, strlen(connection_message), 1) == -1) {
    perror("mq_send");
    return (-1);
  }
  memset(connection_message, 0, strlen(connection_message));
  if (mq_receive(fd, connection_message, sizeof(connection_message), 0) == 1) {
    perror("mq_receive");
    return (-1);
  }
  printf("%s\n", connection_message);
  return 0;
}
int client_message_to_server(mqd_t fd, pid_t pid, int f) {
  printf("Input the message: ");
  char prefix[256];
  char message[246];
  fgets(message, sizeof(message), stdin);
  if (strcmp(message, "exit\n") == 0) {
    f = 0;
  } else {
    sprintf(prefix, "Client %d: %s", pid, message);
    if (mq_send(fd, prefix, strlen(prefix), 1) == -1) {
      perror("mq_send");
      return (-1);
    }
  }
  return f;
}