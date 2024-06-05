#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void my_action(pid_t pid) { printf("Proc %d receice SIGUSR1", pid); }
int main() {
  pid_t pid;
  printf("Input pid\n");
  char buf[256];
  if(!fgets(buf, sizeof(buf), stdin)) {
    return 0; // чтение ввода не удалось
  }
  pid = strtol(buf, NULL, 10);
  printf("%d", pid);
  kill(pid, SIGINT);
}