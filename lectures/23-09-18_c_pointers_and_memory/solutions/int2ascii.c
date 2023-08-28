#include <stdio.h>
#include <assert.h>

int read_int(FILE *f, int *out) {
  int read = fread(out, sizeof(int), 1, f);
  if (read == 1) {
    return 0;
  } else {
    return 1;
  }
}

int main(int argc, char** argv) {
  assert(argc == 2);

  FILE *f = fopen(argv[1], "r");
  assert(f != NULL);

  int x;
  while (read_int(f, &x) == 0) {
    printf("%d\n", x);
  }
}
