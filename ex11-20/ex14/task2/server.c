#include <fcntl.h> //mode_t
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> //mkfifo
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *fifo_name = "my_pipe";
  char *mes = "Hi!";
  if (mkfifo(fifo_name, 0777) == -1) {
    perror("mkfifo");
    return 0;
  }
  if (fork()) {
    execl("./client", "./client", NULL);
  } else {
    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
      perror("server - open");
      return 0;
    }
    write(fd, mes, strlen(mes));
    close(fd);
  }
  return 0;
}