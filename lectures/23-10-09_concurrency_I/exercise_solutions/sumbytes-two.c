#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

struct worker_payload {
  unsigned char* data;
  long* sum;
  pthread_mutex_t* sum_mutex;
  size_t n;
};

void* thread(void* p) {
  struct worker_payload payload = *(struct worker_payload*)p;

  long local_sum = 0;
  for (size_t i = 0; i < payload.n; i++) {
    local_sum += payload.data[i];
  }

  pthread_mutex_lock(payload.sum_mutex);
  *payload.sum += local_sum;
  pthread_mutex_unlock(payload.sum_mutex);

  return NULL;
}

int main(int argc, char** argv) {
  assert(argc == 2);
  char *filename = argv[1];

  // Open the given file and determine its size.
  FILE *file = fopen(filename, "r");
  assert(file != NULL);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // mmap file as an array of 'size' bytes.
  unsigned char *data = mmap(NULL,
                             size,
                             PROT_READ,
                             MAP_PRIVATE,
                             fileno(file), 0);
  assert(data != MAP_FAILED);
  fclose(file);

  long sum = 0;
  pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_t pid1;
  pthread_t pid2;

  struct worker_payload payload1;
  payload1.data = data;
  payload1.sum = &sum;
  payload1.sum_mutex = &sum_mutex;
  payload1.n = size/2;
  assert(pthread_create(&pid1, NULL, thread, &payload1) == 0);

  struct worker_payload payload2;
  payload2.data = &data[size/2];
  payload2.sum = &sum;
  payload2.sum_mutex = &sum_mutex;
  payload2.n = size-size/2;
  assert(pthread_create(&pid2, NULL, thread, &payload2) == 0);

  assert(pthread_join(pid1, NULL) == 0);
  assert(pthread_join(pid2, NULL) == 0);

  printf("Sum: %ld\n", sum);
}
