#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
  pid_t pid = getpid();
  printf("My pid %d\n", pid);
  char *client = "/client_queue"; 
  char *server  = "/server_queue";
  mqd_t client_fd;
  mqd_t server_fd;
  client_fd = mq_open(client, O_RDWR, 0666);
  server_fd = mq_open(server, O_RDWR , 0666);
  
  if ( server_fd == -1) {
    perror("serv - mq_open");
  }
  if (client_fd == -1  ) {
    perror("cl - mq_open");
  }
  char connection_message[256];
  sprintf(connection_message, "Client %d connected to server\n", pid);
  if (mq_send(server_fd, connection_message, strlen(connection_message), 1) == -1) {
    perror("mq_send");

  }
  memset(connection_message, 0, strlen(connection_message));
  sleep(2);
  if (mq_receive(server_fd, connection_message, sizeof(connection_message), 0) == 1) {
    perror("mq_receive");
  }
  printf("%s\n", connection_message);
  int f = 1;
  while (f){
    printf("Input the message: ");
    char prefix[256];
    char message[246];
    fgets(message, sizeof(message), stdin);
    if(strcmp(message,"exit\n") == 0){
      f = 0;
      break;
    }else{
      sprintf(prefix, "Client %d: %s", pid, message);
      if (mq_send(client_fd, prefix, strlen(prefix), 1) == -1) {
        perror("mq_send");
      }
    }
  } 
  char exit_message[256] = "exit";
  printf("%s", exit_message);
  if (mq_send(client_fd, exit_message, strlen(exit_message), 1) == -1) {
    perror("mq_send");
  }
  if (mq_close(client_fd) == -1) {
    perror("mq_close");
  }
  return 0;
}