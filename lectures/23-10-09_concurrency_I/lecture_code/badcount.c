#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile int cnt = 0;

void *thread(void *vargp) {
  int n = *((int*)vargp);

  for (int i = 0; i < n; i++)
    cnt++;

  return NULL;
}

int main(int argc, char **argv) {
  int n = atoi(argv[1]);
  pthread_t tid1, tid2;
  pthread_create(&tid1,
                 NULL,
                 thread,
                 &n);
  pthread_create(&tid2,
                 NULL,
                 thread,
                 &n);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  if (cnt != 2 * n)
    printf("Bad:  %d\n", cnt);
  else
    printf("Good: %d\n", cnt);
}
