#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define TCP_PORT 2000
#define UDP_PORT 2001
#define MAX_EVENTS 10
#define MESSAGE_SIZE 256
#define SERVER "Server"
#define MESSAGE_COUNT 10

int udp_client();
int tcp_client();
int main_function();