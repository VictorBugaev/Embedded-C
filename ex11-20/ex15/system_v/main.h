#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include <stdlib.h>

#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSIZE 256
struct msgbuf {
  long mtype;
  char mtext[MESSIZE];
};