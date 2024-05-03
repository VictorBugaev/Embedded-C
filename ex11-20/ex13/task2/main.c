#include "main.h"
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long a = 0;
int main() {
  pthread_t pthread[N];
  for (int i = 0; i < N; i++) {
    pthread_mutex_lock(&mutex);
    pthread_create(&pthread[i], NULL, calc, NULL);
  }
  for (int i = 0; i < N; i++) {
    pthread_join(pthread[i], NULL);
  }
  printf("%ld", a);
}