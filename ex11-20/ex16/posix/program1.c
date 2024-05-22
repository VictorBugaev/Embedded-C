#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#define LEN 256

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

  char * sem = ".";
  char * shm = "program1";


  if ((sem_fd = sem_open(sem, O_CREAT, 0666, 1)) == -1) {
    perror("semget");
    return -1;
  }

  if ((shm_fd = shm_open(shm, O_CREAT | O_RDWR, 0666)) == -1) {
    perror("shm_open");
    return -1;
  }

  if ((shm_ftruncate(shm_fd, LEN)) == -1) {
    perror("shm_open");
    return -1;
  }

  char *ptr = mmap(NULL, LEN, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);

  if (ptr == (char *)-1) {
    perror("shmat");
    return -1;
  }

 // strncpy(ptr, snd_message, strlen(snd_message));
//  semop(sem_fd, &sem_op, 1);
//  printf("%s\n", ptr);

  if (shmdt(ptr) == -1) {
    perror("shmdt");
    return -1;
  }
  if (shm_unlink(shm) == -1) {
    perror("shmctl");
    return -1;
  }
}