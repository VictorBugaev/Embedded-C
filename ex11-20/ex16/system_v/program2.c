#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
  int sem_fd;
  int fd;
  char *snd_message = "Message from program2";
  char rcv_message[256];
  key_t sem_key = ftok(".", 1);

  if (sem_key == -1) {
    perror("sem ftok");
    return -1;
  }
  key_t key = ftok("program1", 1);
  if (key == -1) {
    perror("ftok");
    return -1;
  }
  if ((sem_fd = semget(key, 1, 0666)) == -1) {
    perror("semget");
    return -1;
  }
  if ((fd = shmget(key, 100, 0)) == -1) {
    perror("shmget");
    return -1;
  }
  char *ptr = (char *)shmat(fd, NULL, 0);
  if (ptr == (char *)-1) {
    perror("shmat");
    return -1;
  }

  printf("%s\n", ptr);
  strncpy(ptr, snd_message, strlen(snd_message));
  semctl(sem_fd, 0, SETVAL, 1);

  if (shmdt(ptr) == -1) {
    perror("shmdt");
    return -1;
  }
}