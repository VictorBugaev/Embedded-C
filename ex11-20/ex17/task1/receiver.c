#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void my_action(int sig, siginfo_t *siginf, void *ptr) {
  pid_t pid;
  printf("Proc receive SIGUSR1 from %d\n", siginf->si_pid);
  kill(pid, SIGKILL);
}

int main() {
  printf("My pid - %d\n", getpid());

  struct sigaction sg = {0};

  sg.sa_sigaction = my_action;
  sg.sa_flags = SA_SIGINFO;

  if (sigaction(SIGUSR1, &sg, NULL) == -1) {
    perror("sigaction");
    return -1;
  }

  while (1) {
  }
  return 0;
}
