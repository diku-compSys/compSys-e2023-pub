#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s argument\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *hello = "hello";
  *hello = 'H';

  fprintf(stdout, "%s, %s!\n", hello, argv[1]);

  return EXIT_SUCCESS;
}
