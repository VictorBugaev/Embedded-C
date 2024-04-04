#include <stdio.h>

#define N 10

int main(){
    int mass[N];
    int count=1;
    int *ptr = mass;
    for (int i = 0; i < N; i++){
        mass[i]=count;
        count+=1;
    }
    for (int i = 0; i < N; i++){
        printf("%d ", *ptr);
        ptr+=1;
    }
    return 0;
}