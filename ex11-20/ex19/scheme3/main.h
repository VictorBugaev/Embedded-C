#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/types.h>
#include <unistd.h>

#define PORT 2000
#define SERVER "Server"

int main_client();
int main_server();
void *new_server();