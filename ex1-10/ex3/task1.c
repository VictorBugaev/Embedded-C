#include <stdio.h>

int main(){
    int num;
    printf("Введите чисоло\n");
    scanf("%d", &num);
    unsigned char *ptr = (unsigned char *)&num;
    for(int i = 1; i <= 4; i++){
        printf("%d-й бит %x\n", i, *ptr);
        ptr++;
        if (i == 2){
            int buf;
            scanf("%d", &buf);    
            *ptr = buf;
            //*ptr = 0xEE;
        }
    }
    printf("Число с изменённым третьим байтом %d\n", num);

    return 0;
}