#include "main.h"
extern pthread_mutex_t mutex;
extern long a;
void *calc(void *arg) {
  for (int i = 0; i < 1000000; i++) {
    a += 1;
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}