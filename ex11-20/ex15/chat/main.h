#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int server_connection(mqd_t fd, struct mq_attr attr);
int server_catch_messages(mqd_t fd, struct mq_attr attr);
int client_connection_to_server(mqd_t fd, pid_t pid);
int client_message_to_server(mqd_t fd, pid_t pid, int f);