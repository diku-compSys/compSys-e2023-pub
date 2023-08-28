#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

size_t file_size(FILE* f) {
  assert(fseek(f, 0, SEEK_END) == 0);
  int end = ftell(f);
  assert(fseek(f, 0, SEEK_SET) == 0);
  return end;
}

int main(int argc, char** argv) {
  assert(argc == 2);
  char *filename = argv[1];

  FILE* f = fopen(filename, "a+");
  assert(f != NULL);

  int len = file_size(f);

  unsigned char *p =
    mmap(NULL, len,
         PROT_READ | PROT_WRITE,
         MAP_SHARED,
         fileno(f), 0);
  assert(p != MAP_FAILED);
  fclose(f);

  for (int i = 0; i < len; i++) {
    p[i] += 1;
  }
}
