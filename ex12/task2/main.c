#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (){
    pid_t child_pid;
    pid_t child_pid2;    
    pid_t grandchild;

    int status;

    child_pid = fork();
    
    if(child_pid == 0){

        printf("\tchild pid - %d\n", getpid());
        printf("\tchild ppid - %d\n", getppid());
        grandchild = fork();
            if(grandchild == 0){
                printf("\t\tgrandchild1 pid - %d\n", getpid());
                printf("\t\tgrandchild1 ppid - %d\n", getppid());
                exit(1);

            }else{
                wait(&status);
                printf("status - %d\n", WEXITSTATUS(status));
            }
        grandchild = fork();
            if(grandchild == 0){
                printf("\t\tgrandchild2 pid - %d\n", getpid());
                printf("\t\tgrandchild2 ppid - %d\n", getppid());
                 exit(2);
            }else{
                wait(&status);
                printf("status - %d\n", WEXITSTATUS(status));
            }
        
        exit(4);
    }else{
        printf("parent pid - %d\n", getpid());
        printf("parent ppid - %d\n", getppid());        
        wait(&status);
        printf("status - %d\n", WEXITSTATUS(status));
    }

    child_pid2 = fork();
    
    if(child_pid2 == 0){

        printf("\tchild2 pid - %d\n", getpid());
        printf("\tchild2 ppid - %d\n", getppid());
        grandchild = fork();
            if(grandchild == 0){
                printf("\t\tgrandchild3 pid - %d\n", getpid());
                printf("\t\tgrandchild3 ppid - %d\n", getppid());
                exit(3);

            }else{
                wait(&status);
                printf("status - %d\n", WEXITSTATUS(status));
            }
        exit(5);

    }else{
        printf("parent pid - %d\n", getpid());
        printf("parent ppid - %d\n", getppid());        
        wait(&status);
        printf("status - %d\n", WEXITSTATUS(status));
    }
    return 0;

}