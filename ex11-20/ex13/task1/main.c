#include <stdio.h>
#include <pthread.h>

#define N 5

void *thread_calc(void *arg){
    int *i = (int *)arg;
    printf("%d", *i);
}

int main(){
    pthread_t thread[N];
    int v[N];
    for(int i = 0; i < N; i ++){
        v[i] = i;
        pthread_create(&thread[i], NULL, thread_calc, (void *)&v[i]);
    }

    for(int r = 0; r < N; r ++){
        pthread_join(thread[r], NULL);
    }
}

