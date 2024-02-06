#include <stdio.h>
#include <time.h>

#define N 3

void matrix();

int main(){
    matrix();    
}
void matrix(){
    int mass[N][N];
        for (int i=0; i < N; i++){
            for(int j=0; j < N; j++){
                mass[i][j] = rand() % 10;
            }
        }
        for (int i=0; i < N; i++){
            for(int j=0; j < N; j++){
                printf("%d ",mass[i][j]);
            }
            printf("\n");
        }
}