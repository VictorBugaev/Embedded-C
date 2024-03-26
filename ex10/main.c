#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
    int fd = open("output.txt", O_CREAT | O_RDWR, 0777);  
    if(fd == -1){
        perror("open");
    }
    char *buf = "String from file";   
    char get_buf[256];
    int str_size = strlen(buf);
    if(write(fd, buf, str_size)==-1){
        perror("write");
        exit(0);

    }
    if(lseek(fd, 0, SEEK_SET)==-1){
        perror("lseek");
        exit(0);

    }
    
    for(int i = 0; (str_size + 1) - i > 0; i++){
        if(lseek(fd, str_size - i, SEEK_SET)==-1){
            perror("lseek");
            exit(0);

        }
        if(read(fd, get_buf, strlen(buf)) == -1){
            perror("read");
            exit(0);
        }
    }
    printf("%s\n", get_buf);    
}