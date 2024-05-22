#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>


int main(){
    key_t key = ftok("shared_memory", 1);
    int fd;
    char *snd_message = "Message from program2";
    char rcv_message[256];
    if(key == -1){
        perror("ftok");
        return -1;
    }
    if((fd = shmget(key, 100, 0)) == -1){
        perror("shmget");
        return -1;
    }
    char *ptr = (char *)shmat(fd, NULL, 0);
    if(ptr == (char *)-1){
        perror("shmat");
        return -1;
    }   
    //while(1){
        //strncpy(rcv_message, ptr, 100);
        printf("%s", ptr);
        //sleep(10);
        strncpy(ptr, snd_message, strlen(snd_message));
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