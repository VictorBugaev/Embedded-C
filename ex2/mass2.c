#include <stdio.h>

#define N 5

void reverb();

int main(){
   reverb();
}

void reverb(){
    int mass[N];
    for (int i=0; i < N; i++){
        scanf("%d", &mass[i]);
    }
    for (int i = N - 1; i >= 0; i--){
        printf("%d ",mass[i]);
    }
}