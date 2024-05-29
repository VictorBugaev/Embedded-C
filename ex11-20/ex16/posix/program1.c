#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define LEN 256

int main() {
  int shm_fd;
  char *snd_message = "Message from program1";
  char rcv_message[256];

  const char *sem = "sem";
  const char *shm = "shm";

  sem_t *sem_fd = sem_open(sem, O_CREAT, 0666, 1);

  if (sem_fd == SEM_FAILED) {
    perror("sem_open");
    return -1;
  }

  if ((shm_fd = shm_open(shm, O_CREAT | O_RDWR, 0666)) == -1) {
    perror("shm_open");
    return -1;
  }

  if ((ftruncate(shm_fd, LEN)) == -1) {
    perror("ftruncate");
    return -1;
  }

  char *ptr = mmap(NULL, LEN, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

  if (ptr == (char *)-1) {
    perror("mmap");
    return -1;
  }

  strncpy(ptr, snd_message, strlen(snd_message));
  sem_wait(sem_fd);
  printf("Message sent: %s\n", ptr);

  if (munmap(ptr, LEN) == -1) {
    perror("munmap");
    return -1;
  }
  if (shm_unlink(shm) == -1) {
    perror("shm_unlink");
    return -1;
  }
}