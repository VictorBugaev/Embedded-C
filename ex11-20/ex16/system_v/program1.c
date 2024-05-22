#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>

int main(){
    key_t key = ftok("shared_memory", 1);

    key_t sem_key = ftok(".", 1);
    if(sem_key == -1){
        perror("sem ftok");
        return -1;
    }
    int sem_fd;
    if((sem_fd = semget(sem_fd, 1, IPC_CREAT | 0666)) == -1){
        perror("semget");
        return -1;
    }
    semctl (sem_fd, 0, SETVAL, 1);
    struct sembuf sem_op;

    for (int i = 0; i < MAX_COUNT; i++) {
        sem_op.sem_num = 0;
        sem_op.sem_op = -1; // Decrement semaphore
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1)
    int fd;
    char *snd_message = "Message from program1";
    char rcv_message[256];
    if(key == -1){
        perror("ftok");
        return -1;
    }
    if((fd = shmget(key, 100, IPC_CREAT | 0666)) == -1){
        perror("shmget");
        return -1;
    }
    char *ptr = (char *)shmat(fd, NULL, 0);
    if(ptr == (char *)-1){
        perror("shmat");
        return -1;
    }   
        printf("sem = %d\n", res);
        strncpy(ptr, snd_message, strlen(snd_message));
        //semctl (sem_fd, 0, SETVAL, -1);
        //strncpy(rcv_message, ptr, 100);
        printf("%s\n", ptr);
           
    //}


    if(shmdt(ptr) == -1){
        perror ("shmdt");
        return -1;
    }
    if(shmctl(fd, IPC_RMID, 0) == -1){
        perror ("shmctl");
        return -1;    
    }
}