#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_COUNT 5
#define MAIN_PORT 3000
#define ADDRESS "Server"
#define MESSAGE_SIZE 256

struct sub_server {
  int port;
  int availible;
  int fd;
  int count;
};

int create_pull(int port);
void *connection_to_subserver(void *arg);
int create_main_server(struct sub_server *mass);
int create_a_client(int port, char *message);
