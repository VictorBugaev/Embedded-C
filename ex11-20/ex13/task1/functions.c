#include "main.h"
pthread_mutex_t mutex;

void *thread_calc(void *arg) {
  int *i = (int *)arg;
  printf("%d", *i);
  pthread_mutex_unlock(&mutex);
}