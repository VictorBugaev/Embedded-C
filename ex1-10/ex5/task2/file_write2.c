#include <stdio.h>
#include <stdlib.h>

int main(){
    char fname[] = "input.txt";
    unsigned char str[] = {  
                    '1', '1', '1', '1', 
                    '1', '1', '1', '1', 
                    '1', '1', '1', '1', 
                    0x0, 0x0, 0x0, 0x0,
                    0x0, 0x0, 0x0, 0x0,
                    0xf7, 0x17, 0x40
                    };
    int i = 0;
    int size = sizeof(str);
    printf("size =  %d\n", size);
    while(i < size){
        printf("%d - %x\n", str[i], str[i]);
        ++i;
    }

    printf("str = %s\n", str);
    FILE *file = fopen(fname, "w");
    fwrite(str, sizeof(char), size, file);
    fclose(file);
    return 0;
}



