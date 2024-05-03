#include "main.h"

extern int client[N];
extern int shop[N];
extern pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
extern pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *create_client(void * arg){
    int *count = (int *)arg;
    client[*count] = rand() % 2000 + 9000; 
    printf("client - %d\n", client[*count]);
    pthread_mutex_unlock(&mutex);
}
void *supplier(void * arg){
    int *count = (int *)(arg);
    shop[*count] = 10000;
    pthread_mutex_unlock(&mutex2);
}


void * buy(void *arg){ 
    int *count = (int *)arg;
    while(client[*count] > 0){
        if(client[*count] > shop[*count]){
            client[*count] -= shop[*count];
            shop[*count] = 0;
        }else{
            shop[*count] -= client[*count];
            client[*count] = 0;
        }
        pthread_t sup;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex2);
        pthread_create(&sup, NULL, supplier, (void*)&(*count));
        pthread_join(sup, NULL);
    }
    printf("shop[%d] -  %d, client[%d] - %d\n", *count, shop[*count], *count, client[*count]);
}
