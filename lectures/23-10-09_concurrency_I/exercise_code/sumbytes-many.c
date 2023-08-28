#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

// TODO: add fields here.
struct worker_payload {
  int dummy; //remove this
};

void* thread(void* p) {
  struct worker_payload work = *(struct worker_payload*)p;

  // TODO

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
  long sum = 0; // TODO: also create mutex.

  // TODO: create 'nthreads' threads.  Thread 'i' should sum from
  // data[i*chunk_size] to data[(i+1)*chunk_size] - but note that the
  // last thread may read out-of-bounds if the file size is not
  // divisible by the chunk size!  Make sure you avoid this by making
  // the chunk size smaller for the last thread.

  for (int i = 0; i < nthreads; i++) {
    // TODO: initialise payloads[i] and launch thread 'i'.
  }

  for (int i = 0; i < nthreads; i++) {
    // Wait for thread 'i' to finish.
  }

  printf("Sum: %ld\n", sum);
}
