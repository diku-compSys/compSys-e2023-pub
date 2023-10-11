#include <stdio.h>
#include <pthread.h>

char **ptr;
int cnt = 0;

void* thread(void *vargp) {
  int j = (int)vargp;

  printf("%d: %s (cnt=%d)\n",
         j, ptr[j], ++cnt);
  return NULL;
}

int main() {
  pthread_t tid;
  char *msgs[2] = {
    "Hello from foo",
    "Hello from bar"
  };
  ptr = msgs;
  for (int i = 0; i < 2; i++)
    pthread_create(&tid,
                   NULL,
                   thread,
                   (void *)i);
  pthread_exit(NULL);
}