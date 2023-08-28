#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int fib (int n) {
  if (n < 2) {
    return 1;
  } else {
    return fib(n-1) + fib(n-2);
  }
}

void* fib_thread(void* arg) {
  char *line = arg;
  int n = atoi(line);
  printf("fib(%d) = %d\n", n, fib(n));
  free(arg);
  return NULL;
}

int main() {
  char *line = NULL;
  ssize_t line_len;
  size_t buf_len = 0;

  int i = 0;
  pthread_t threads[200000];

  while ((line_len = getline(&line, &buf_len, stdin)) != -1) {
    pthread_create(&threads[i], NULL, fib_thread, strdup(line));
    i++;
  }

  for (int j = 0; j < i; j++) {
    pthread_join(threads[j], NULL);
  }

  free(line);
}
