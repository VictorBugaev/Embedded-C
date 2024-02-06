#include <stdio.h>

#define N 5

void mass();

int main(){
    mass();
}

void mass(){
    int matrix[N][N];
    int k;
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matrix[i][j]=0;
            k = i;
            while (k>=0)
            {  
               matrix[i][N-k-1] = 1;  
               k--;

            }            
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}