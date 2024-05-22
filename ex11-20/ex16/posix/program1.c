#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#define LEN 256

int main() {
  sem_t * sem_fd;
  int shm_fd;
  char *snd_message = "Message from program1";
  char rcv_message[256];

  char * sem = ".";
  const char * shm = "/shm";


  if ((sem_fd = sem_open(sem, O_RDWR, 0666, 1)) == (sem_t *) -1) {
    perror("semget");
    return -1;
  }

  if ((shm_fd = shm_open(shm, O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1) {
    perror("shm_open");
    return -1;
  }

  if ((ftruncate(shm_fd, LEN)) == -1) {
    perror("shm_open");
    return -1;
  }

  char *ptr = mmap(NULL, LEN, PROT_WRITE|PROT_READ, MAP_SHARED, shm_fd, 0);

  if (ptr == (char *)-1) {
    perror("shmat");
    return -1;
  }
  sem_wait(sem_fd); // Ждем, пока семафор не станет доступен

  sem_wait(sem_fd); // Ждем, пока семафор не станет доступен
  strncpy(ptr, snd_message, strlen(snd_message));
  sem_post(sem_fd); // Освобождаем семафор

  printf("Message sent: %s\n", ptr);
  if (munmap(ptr, LEN) == -1) {
    perror("shmdt");
    return -1;
  }
  if (shm_unlink(shm) == -1) {
    perror("shmctl");
    return -1;
  }
}