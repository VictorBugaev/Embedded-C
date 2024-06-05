#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void do_nothink() {}

int main() {
  printf("mypid = %d\n", getpid());

  struct sigaction sa;
  sa.sa_sigaction = do_nothink;
  if (sigfillset(&sa.sa_mask) == -1 || sigaction(SIGUSR1, &sa, NULL) == -1) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  sigset_t signalSet;
  if (sigemptyset(&signalSet)) {
    perror("sigemptyset");
    return -1;
  }
  if (sigfillset(&signalSet)) {
    perror("sigfillset");
    return -1;
  }
  int sig;
  while (1) {
    sigwait(&signalSet, &sig);
    printf("sig = %d\n", sig);
  }
  printf("End\n");
  return 0;
}