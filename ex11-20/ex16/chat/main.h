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

void main_server_function(sem_t *sem_fd, char *serv_ptr, char *client_ptr);
void connection_to_server(char *serv_ptr, pid_t pid);
void message_to_server(char *client_ptr, pid_t pid, sem_t *sem_fd);