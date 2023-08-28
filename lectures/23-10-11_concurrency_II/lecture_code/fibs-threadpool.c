#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int fib (int n) {
  if (n < 2) {
    return 1;
  } else {
    return fib(n-1) + fib(n-2);
  }
}

pthread_cond_t line_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t line_mutex = PTHREAD_MUTEX_INITIALIZER;
char *volatile line = NULL;
volatile int die = 0;

void* worker(void* arg) {
  arg=arg;
  int done = 0;

  while (!done) {
    char *my_line = NULL;
    assert(pthread_mutex_lock(&line_mutex) == 0);

    if (line == NULL && !die) {
      pthread_cond_wait(&line_cond, &line_mutex);
    } else if (line == NULL && die) {
      done = 1;
    } else if (line != NULL) {
      my_line = line;
      line = NULL;
      pthread_cond_broadcast(&line_cond);
    }

    assert(pthread_mutex_unlock(&line_mutex) == 0);

    if (my_line != NULL) {
      int n = atoi(my_line);
      printf("fib(%d) = %d\n", n, fib(n));
      free(my_line);
    }
  }

  return NULL;
}

int main() {
  char *my_line = NULL;
  ssize_t line_len;
  size_t buf_len = 0;

  // Create the threads.
  int num_threads = sysconf(_SC_NPROCESSORS_ONLN);
  pthread_t *threads = malloc(num_threads*sizeof(pthread_t));
  for (int i = 0; i < num_threads; i++) {
    pthread_create(&threads[i], NULL, worker, NULL);
  }

  while ((line_len = getline(&my_line, &buf_len, stdin)) != -1) {
    int done = 0;
    while (!done) {
      assert(pthread_mutex_lock(&line_mutex) == 0);
      if (line == NULL) {
        line = strdup(my_line);
        pthread_cond_signal(&line_cond);
        done = 1;
      } else {
        pthread_cond_wait(&line_cond, &line_mutex);
      }
      assert(pthread_mutex_unlock(&line_mutex) == 0);
    }
  }

  assert(pthread_mutex_lock(&line_mutex) == 0);
  die = 1;
  pthread_cond_broadcast(&line_cond);
  assert(pthread_mutex_unlock(&line_mutex) == 0);

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  free(my_line);
}
