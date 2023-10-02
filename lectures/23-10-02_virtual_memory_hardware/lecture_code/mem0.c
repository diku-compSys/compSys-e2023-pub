#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
  (void)argc;
  size_t num_gib = atoi(argv[1]);
  size_t to_alloc = num_gib * 1024 * 1024 * 1024;

  printf("allocating %ld bytes\n", (long)to_alloc);

  unsigned char *p = malloc(to_alloc);
  assert(p != NULL);

  printf("spinning\n");

  if (p) {
    while (1) ;
  }
}
