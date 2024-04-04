#include <stdio.h>
#include <string.h>

int main(){
    int f = 1;
    char str[256];
    char sub_str[256];
    printf("Введите строку:\n");
    scanf("%s", str);
    printf("Введите подстроку:\n");
    scanf("%s", sub_str);
    char *ptr = strstr(str, sub_str);
    if (ptr)
    {
        printf("%s", sub_str);
    }else{
        printf("NULL");
    }
    return 0;
}