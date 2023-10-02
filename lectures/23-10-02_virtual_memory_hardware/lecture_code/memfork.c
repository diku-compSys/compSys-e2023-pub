#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char** argv) {
  (void)argc;
  size_t num_gib = atoi(argv[1]);
  int num_procs = atoi(argv[2]);
  size_t to_alloc = num_gib * 1024 * 1024 * 1024;

  printf("allocating %ld bytes\n", (long)to_alloc);

  unsigned char *p = malloc(to_alloc);
  assert(p != NULL);

  printf("initialising\n");

  for (size_t i = 0; i < to_alloc; i++) {
    p[i] = rand();
  }

  printf("spinning\n");

  for (int i = 0; i < num_procs; i++) {
    if (fork() == 0) {
      // In child.
      while (1) ;
    }
  }

  while (1) ;
}
