#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

struct worker_payload {
  unsigned char *data;
  size_t start;
  size_t end;
  long* sum;
  pthread_mutex_t* sum_mutex;
};

void* thread(void* p) {
  struct worker_payload work = *(struct worker_payload*)p;

  long local_sum = 0;

  for (size_t i = work.start; i < work.end; i++) {
    local_sum += work.data[i];
  }

  pthread_mutex_lock(work.sum_mutex);
  *work.sum += local_sum;
  pthread_mutex_unlock(work.sum_mutex);

  return NULL;
}

int main(int argc, char** argv) {
  assert(argc == 3);
  int nthreads = atoi(argv[1]);
  char *filename = argv[2];

  // Open the given file and determine its size.
  FILE* file = fopen(filename, "r");
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

  pthread_t ptids[nthreads];
  struct worker_payload payloads[nthreads];
  int chunk_size = (size + nthreads - 1) / nthreads;
  long sum = 0;
  pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

  for (int i = 0; i < nthreads; i++) {
    payloads[i].data = data;
    payloads[i].start = i * chunk_size;
    payloads[i].end = (i+1) * chunk_size;
    payloads[i].sum = &sum;
    payloads[i].sum_mutex = &sum_mutex;
    if (payloads[i].end > size) {
      payloads[i].end = size;
    }

    assert(pthread_create(&ptids[i], NULL, thread, &payloads[i]) == 0);
  }

  for (int i = 0; i < nthreads; i++) {
    assert(pthread_join(ptids[i], NULL) == 0);
  }

  printf("Sum: %ld\n", sum);
}
