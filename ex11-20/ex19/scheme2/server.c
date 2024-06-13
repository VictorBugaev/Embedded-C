#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "main.h"

int main() {
  struct sub_server subserver_pull[SERVER_COUNT];

  for (int i = 0; i < SERVER_COUNT; i++) {
    subserver_pull[i].port = 2000 + i + 1;
    subserver_pull[i].fd = create_pull(subserver_pull[i].port);
    subserver_pull[i].availible = 1;
    subserver_pull[i].count = i + 1;
    printf("Subserver %d fd %d\n", subserver_pull[i].count,
           subserver_pull[i].fd);
  }
  create_main_server(subserver_pull);
}
