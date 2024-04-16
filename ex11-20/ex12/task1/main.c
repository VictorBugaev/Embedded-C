#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(){
    pid_t child_pid;
    int status;

    child_pid = fork();
    if(child_pid == 0){
        printf("child pid - %d\n", getpid());
        printf("child ppid - %d\n", getppid());
        exit(1);
    }else{
        printf("parent pid - %d\n", getpid());
        printf("parent ppid - %d\n", getppid());        
        wait(&status);
        printf("status - %d\n", WEXITSTATUS(status));
    }
    return 0;

}