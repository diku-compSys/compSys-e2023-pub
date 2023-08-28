#include <pthread.h>
#include <assert.h>
#include <stdio.h>

void* thread(void *arg) {
  int* p = arg;
  printf("Hello world! %d\n", *p);
  return NULL;
}

int main() {
  int x = 42;
  pthread_t tid;
  assert(pthread_create(&tid, NULL, thread, &x) == 0);
  assert(pthread_join(tid, NULL) == 0);
}
