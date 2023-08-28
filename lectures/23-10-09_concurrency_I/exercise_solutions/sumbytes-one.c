#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

int main(int argc, char** argv) {
  assert(argc == 2);
  char *filename = argv[1];

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

  long sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += data[i];
  }

  printf("sum: %ld\n", sum);
}
