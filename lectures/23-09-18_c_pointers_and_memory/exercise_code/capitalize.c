#include <stdio.h>
#include <stdlib.h>

// Inline capitalisation of an input text.

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s argument\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *str = argv[1];

  printf("Input string: %s\n", str);

  while (*str != 0) {
    if (97 <= *str && *str <= 122) {
       str -= 32;
    }
    str++;
  }
  printf("Capitalised string: %s\n", argv[1]);
  return EXIT_SUCCESS;

}
