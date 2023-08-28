#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

int main() {
  FILE *f = fopen("file", "r");
  assert(f != NULL);

  char c;
  assert(fread(&c, sizeof(char), 1, f) == 1);

  printf("Read: %c\n", c);

  pid_t ret = fork();

  if (ret == 0) {
    // Child
    assert(fread(&c, sizeof(char), 1, f) == 1);
    printf("Child read: %c\n", c);
    fclose(f);
  } else {
    // Parent
    assert(fread(&c, sizeof(char), 1, f) == 1);
    printf("Parent read: %c\n", c);
    fclose(f);

    // Wait for child.
    waitpid(ret, NULL, 0);
  }
}
