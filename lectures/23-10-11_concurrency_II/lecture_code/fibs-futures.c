#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include "futures.h"

static const int PAR_THRESHOLD = 30;

int fib (int n);

void* fib_thread(void *arg) {
  int *r = malloc(sizeof(int));
  int n = *(int*)arg;

  *r = fib(n);

  return r;
}

int fib (int n) {
  if (n < 2) {
    return 1;
  } else {
    if (n >= PAR_THRESHOLD) {
      int *x, *y;
      int n1 = n-1, n2 = n-2;
      struct future *f1 = future_create(fib_thread, &n1);
      struct future *f2 = future_create(fib_thread, &n2);
      x = future_get(f1);
      y = future_get(f2);
      return *x + *y;
    } else {
      return fib(n-1) + fib(n-2);
    }
  }
}

int main() {
  char *line = NULL;
  ssize_t line_len;
  size_t buf_len = 0;

  while ((line_len = getline(&line, &buf_len, stdin)) != -1) {
    int n = atoi(line);
    printf("fib(%d) = %d\n", n, fib(n));
  }

  free(line);
}
