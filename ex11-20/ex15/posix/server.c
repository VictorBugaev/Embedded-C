#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> /* For mode constants */

int main() {
  char *mq_name = "/mqueue";
  mqd_t fd;
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 256;
  attr.mq_curmsgs = 0;
  fd = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);
  if (fd == -1) {
    perror("mq_open");
  }
  char buffer[256]; //= "";
  if (mq_receive(fd, buffer, sizeof(buffer), 0) == 1) {
    perror("mq_receive");
  }
  printf("%s", buffer);
  memset(buffer, 0, strlen(buffer));
  char *message = "You connected to the server!";
  strncpy(buffer, message, strlen(message));
  if (mq_send(fd, buffer, strlen(buffer), 1) == -1) {
    perror("mq_send");
  }

  if (mq_close(fd) == -1) {
    perror("mq_close");
  }
  if (mq_unlink(mq_name) == -1) {
    perror("mq_unlink");
  }
  return 0;
}