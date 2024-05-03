#include "main.h"
#include <pthread.h>
#include <stdio.h>
extern pthread_mutex_t mutex;

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t thread[N];
  int v[N];
  for (int i = 0; i < N; i++) {
    v[i] = i;
    pthread_mutex_lock(&mutex);
    pthread_create(&thread[i], NULL, thread_calc, (void *)&v[i]);
  }

  for (int r = 0; r < N; r++) {
    pthread_join(thread[r], NULL);
  }
}
