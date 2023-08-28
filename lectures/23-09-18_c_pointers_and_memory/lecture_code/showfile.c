#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Nej!\n");
    return 1;
  }

  FILE* f = fopen(argv[1], "r");
  assert(f != NULL);

  unsigned char b;
  int e;

  while (1) {
    e = fread(&b, 1, 1, f);
    if (e == 0) {
      break;
    }

    printf("%d ", b);
    e = fwrite(&b, 1, 1, stdout);
    assert(e == 1);
    printf("\n");
  }

  assert(fclose(f) == 0);
}
