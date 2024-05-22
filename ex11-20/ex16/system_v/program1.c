#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
int main() {
  int sem_fd;
  int fd;
  char *snd_message = "Message from program1";
  char rcv_message[256];
  semctl(sem_fd, 0, SETVAL, 0);
  struct sembuf sem_op;
  sem_op.sem_num = 0;
  sem_op.sem_op = -1;
  sem_op.sem_flg = 0;

  key_t key = ftok("program1", 1);

  key_t sem_key = ftok(".", 1);
  if (sem_key == -1) {
    perror("sem ftok");
    return -1;
  }

  if ((sem_fd = semget(key, 1, IPC_CREAT | 0666)) == -1) {
    perror("semget");
    return -1;
  }

  if (key == -1 || sem_key == -1) {
    perror("ftok");
    return -1;
  }

  if ((fd = shmget(key, 100, IPC_CREAT | 0666)) == -1) {
    perror("shmget");
    return -1;
  }
  char *ptr = (char *)shmat(fd, NULL, 0);
  if (ptr == (char *)-1) {
    perror("shmat");
    return -1;
  }

  strncpy(ptr, snd_message, strlen(snd_message));
  semop(sem_fd, &sem_op, 1);
  printf("%s\n", ptr);

  if (shmdt(ptr) == -1) {
    perror("shmdt");
    return -1;
  }
  if (shmctl(fd, IPC_RMID, 0) == -1) {
    perror("shmctl");
    return -1;
  }
}