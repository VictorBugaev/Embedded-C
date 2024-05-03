#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define N 5

void *create_client(void * arg);
void *supplier(void * arg);
void * buy(void *arg);