#include <stdio.h>

#define N 5

void snail();

int main(){
    snail();
}

void snail(){
    int matrix[N][N];
    int count = 1;
    int num=10;
    int top = 0;
    int bottom = N-1;
    int left = 0;
    int right = N-1;
    int x=0,y=0;
    while (count < N*N)
    {
        for(x; x <= right; x++){
            matrix[top][x]=num;
            count++;
            num++;
        }  
        top+=1;
        y+=1;
        for(y; y <= bottom;y++){
            matrix[y][right]=num;
            count++;
            num++;
        }
        right-=1;
        x-=2;
        for(x; x > left; x--){
            matrix[bottom][x]=num;
            count++;
            num++;
        }
        y-=1;
        bottom-=1; 
        for(y; y > top; y--){
            matrix[y][left]=num;
            count++;
            num++;
        }
        left+=1;
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");

    }
}