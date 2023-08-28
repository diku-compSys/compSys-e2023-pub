#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
  assert(argc == 2);

  FILE *f = fopen(argv[1], "r");
  assert(f != NULL);

  char c;

  while (fread(&c, sizeof(c), 1, f) == 1) {
    printf("%.2x\n", (int)c);
  }
}
