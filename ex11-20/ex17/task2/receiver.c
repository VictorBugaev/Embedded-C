#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  
  printf("My pid - %d\n", getpid());
  sigset_t newset;
  sigemptyset(&newset);
  sigaddset(&newset, SIGINT);
  sigprocmask(SIG_BLOCK, &newset, 0);
  pause();
  return 0;
}