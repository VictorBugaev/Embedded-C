#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> /* For mode constants */
#include <stdlib.h>

int main() {  
  char *client = "/client_queue"; 
  char *server  = "/server_queue";
  mqd_t client_fd;
  mqd_t server_fd;
  int f = 1;

  struct mq_attr attr;
  attr.mq_flags = 0;//O_NONBLOCK;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 256;
  attr.mq_curmsgs = 0;
  client_fd = mq_open(client, O_CREAT | O_RDWR | O_NONBLOCK  , 0666, &attr);
  server_fd = mq_open(server, O_CREAT | O_RDWR , 0666, &attr);
  if ( server_fd == -1) {
    perror("serv - mq_open");
  }
  if (client_fd == -1  ) {
    perror("cl - mq_open");
  }
     
    

  while(f){
    char client_message[256];
    char server_message[256];
    if (mq_receive(server_fd, server_message, sizeof(server_message), NULL) != -1 | errno == EAGAIN) {
      if(errno != EAGAIN){
        printf("%s\n", server_message);
        memset(server_message, 0, strlen(server_message));
        char *message = "You connected to the server! Write your message\n";
        strncpy(server_message, message, strlen(message));
        if (mq_send(server_fd, server_message, strlen(server_message), 1) == -1) {
          perror("mq_send");
        }
        attr.mq_flags = O_NONBLOCK;
        if (mq_setattr(server_fd, &attr, NULL)){
          perror("mq_setattr");
          return -1;
        }
      }
    } else{
      perror("server mq_receive");
      return -1;
    }
    if (mq_receive(client_fd, client_message, sizeof(client_message), 0) == -1 && errno != EAGAIN) {
      //printf("%s", wr)
      perror("client mq_receive");
    }
    sleep(2);
    if(strcmp(client_message,"exit") == 0){
      printf("Client leave the chat\n");   
    }else{
      printf("%s\n", client_message);
    }
    memset(client_message, 0, strlen(client_message));
  }

  if (mq_close(client_fd) == -1) {
    perror("mq_close");
  }
  if (mq_unlink(client) == -1) {
    perror("mq_unlink");
  }
  return 0;
}