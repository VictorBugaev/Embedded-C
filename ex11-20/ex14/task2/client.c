#include <fcntl.h> //mode_t
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //mkfifo
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char buf[256];
  char *fifo_name = "my_pipe";
  int fd = open(fifo_name, O_RDONLY | O_NONBLOCK);
  if (fd == -1) {
    perror("client - open");
    return 0;
  }
  sleep(1);
  if (read(fd, buf, sizeof(buf)) == -1) {
    perror("read");
  }
  close(fd);

  printf("Message from server - %s", buf);
  
  return 0;
}