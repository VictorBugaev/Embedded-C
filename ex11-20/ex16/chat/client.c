#include "main.h"
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

int main() {
  int serv_fd;
  int client_fd;
  pid_t pid = getpid();
  const char *sem = "sem";
  const char *serv_shm = "serv_shm";
  const char *client_shm = "client_shm";

  sem_t *sem_fd = sem_open(sem, 0666, 1);

  if (sem_fd == SEM_FAILED) {
    perror("sem_open");
    return -1;
  }

  if ((serv_fd = shm_open(serv_shm, O_RDWR, 0666)) == -1) {
    perror("serv - shm_open");
    return -1;
  }

  if ((client_fd = shm_open(client_shm, O_RDWR, 0666)) == -1) {
    perror("client - shm_open");
    return -1;
  }

  if ((ftruncate(serv_fd, LEN)) == -1) {
    perror("serv - ftruncate");
    return -1;
  }

  if ((ftruncate(client_fd, LEN)) == -1) {
    perror("client - ftruncate");
    return -1;
  }
  sem_post(sem_fd);

  char *serv_ptr =
      mmap(NULL, LEN, PROT_WRITE | PROT_READ, MAP_SHARED, serv_fd, 0);
  char *client_ptr =
      mmap(NULL, LEN, PROT_WRITE | PROT_READ, MAP_SHARED, client_fd, 0);

  if ((serv_ptr && client_ptr) == -1) {
    perror("mmap");
    return -1;
  }

  connection_to_server(serv_ptr, pid);
  message_to_server(client_ptr, pid, sem_fd);

  if (munmap(serv_ptr, LEN) == -1) {
    perror("munmap");
    return -1;
  }
  if (munmap(client_ptr, LEN) == -1) {
    perror("munmap");
    return -1;
  }
}