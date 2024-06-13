#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "main.h"

int main() {
  pid_t pid = getpid();
  char message[256];
  sprintf(message, "Client pid %d connect to the main serever\n", pid);

  int new_port = create_a_client(MAIN_PORT, message);

  memset(message, 0, MESSAGE_SIZE);
  sprintf(message, "Message to the subserver\n");
  create_a_client(new_port, message);
}
