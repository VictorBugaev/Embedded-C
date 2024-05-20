#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> /* For mode constants */

int main() {
  char *mq_name = "/mqueue";
  mqd_t fd;
  fd = mq_open(mq_name, O_RDWR);
  if (fd == -1) {
    perror("mq_open");
  }

  char buffer[256] = "Message from the client !";

  if (mq_send(fd, buffer, strlen(buffer), 0) == -1) {
    perror("mq_send");
  }

  memset(buffer, 0, strlen(buffer));

  if (mq_receive(fd, buffer, sizeof(buffer), 0) == 1) {
    perror("mq_receive");
  }

  printf("%s", buffer);

  if (mq_close(fd) == -1) {
    perror("mq_close");
  }
  return 0;
}