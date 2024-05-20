#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include <stdlib.h>

#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "main.h"

int main() {
  char *queue_name = "./server.c";
  key_t key = ftok(queue_name, 1);
  if (key == -1) {
    perror("ftok");
    return -1;
  }
  int id = msgget(key, IPC_CREAT | 0600);
  if (id == -1) {
    perror("msgget");
    return -1;
  }
  struct msgbuf msg;

  if (msgrcv(id, &msg, MESSIZE, 1, 0) == -1) {
    perror("msgrcv");
    return -1;
  }
  printf("Message from the server: %s", msg.mtext);
  msg.mtype = 2;

  char *message = "Hi!";
  memset(msg.mtext, 0, sizeof(msg.mtext));
  strncpy(msg.mtext, message, strlen(message));
  if (msgsnd(id, &msg, strlen(msg.mtext), 0) == -1) {
    perror("msgsnd");
    return -1;
  }
}