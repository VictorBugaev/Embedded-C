#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
    int fd = open("output.txt", O_CREAT || O_RDWR);  
    if(fd == -1){
        perror("open");
    }
    char *buf = "String from file";   
    char *get_buf;
    int str_size = strlen(buf);
    write(fd, buf, str_size);   
    if(lseek(fd, 0, str_size)==-1){
        perror("lseek");
    }
    int pos = 1;
    while(str_size - pos){
        if(lseek(fd, str_size - pos, 1)==-1){
            perror("lseek");
        }
        read(fd, get_buf, 1);
        printf("%s\n", get_buf);
        pos++;
    }
}