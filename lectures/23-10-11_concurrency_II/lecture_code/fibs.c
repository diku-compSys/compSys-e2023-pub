#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int fib (int n) {
  if (n < 2) {
    return 1;
  } else {
    return fib(n-1) + fib(n-2);
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
