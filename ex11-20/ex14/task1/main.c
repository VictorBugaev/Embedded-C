#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
  int status;
  char messsage[10] = "Hi";
  char buffer[10];
  int fd[2];
  pipe(fd);
  if (fork()) {
    close(fd[0]);
    write(fd[1], messsage, strlen(messsage));
    wait(&status);
  } else {
    close(fd[1]);
    read(fd[0], buffer, sizeof(buffer));
    printf("%s", buffer);
    exit(1);
  }
  return 0;
}
