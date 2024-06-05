#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  printf("Input pid\n");
  char buf[256];
  if(!fgets(buf, sizeof(buf), stdin)) {
    return 0; // чтение ввода не удалось
  }

  pid = strtol(buf, NULL, 10);
  printf("%d", pid);
  kill(pid, SIGUSR1);
}