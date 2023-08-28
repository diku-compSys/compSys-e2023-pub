#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

// TODO: add fields here.
struct worker_payload {
  int dummy; // remove this.
};

void* thread(void* p) {
  struct worker_payload payload = *(struct worker_payload*)p;

  // TODO: add code here.

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

  // TODO: Create a mutex protecting 'sum'.

  // TODO: Launch two threads which receive as payload:
  //  * 'data'.
  //  * Start and end offsets in 'data' indicating which part of the
  //    array each thread should traverse.
  //  * a pointer to 'sum' it can update.
  //  * a pointer to a mutex protecting 'sum'.

  // TODO: join the two threads.

  printf("Sum: %ld\n", sum);
}
