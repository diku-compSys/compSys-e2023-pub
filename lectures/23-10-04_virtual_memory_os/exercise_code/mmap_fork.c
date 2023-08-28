// Demonstrates sharing memory between parent and child.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <assert.h>

size_t file_size(FILE* f) {
  assert(fseek(f, 0, SEEK_END) == 0);
  int end = ftell(f);
  assert(fseek(f, 0, SEEK_SET) == 0);
  return end;
}

int main(int argc, char** argv) {
  assert(argc == 2);
  char *filename = argv[1];

  FILE* f = fopen(filename, "r");
  assert(f != NULL);
  size_t size = file_size(f);

  unsigned char *data = mmap(NULL,
                             size,
                             PROT_WRITE | PROT_READ,
                             MAP_ANONYMOUS | MAP_SHARED,
                             0, 0);
  assert(data != MAP_FAILED);

  pid_t pid = fork();
  if (pid == 0) {
    assert(fread(data, 1, size, f) == size);
    exit(0);
  } else {
    fclose(f);
    waitpid(pid, NULL, 0);
    for (size_t i = 0; i < size; i++) {
      putchar(data[i]);
    }
  }
}
