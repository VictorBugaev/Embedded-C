#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"

int client[N];
int shop[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int main(){
    pthread_t pthread[N];
    int v[N];
    srand(time(0));
    for(int i = 0; i < N; i++){
        shop[i] = 10000;
    }
    for(int i = 0; i < N; i++){
        v[i] = i;
        pthread_mutex_lock(&mutex);
        pthread_create(&pthread[i], NULL, create_client, (void *)&v[i]);
    }
    for(int k = 0; k < N; k++){
        pthread_join(pthread[k], NULL);    
    }
    for(int i = 0; i < N; i++){
        pthread_mutex_lock(&mutex);
        pthread_create(&pthread[i], NULL, buy, (void *)&v[i]);
        
    }
    for(int i = 0; i < N; i++){
        pthread_join(pthread[i], NULL);    
    }
}