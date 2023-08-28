#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <fcntl.h>

int main() {
  int fd = open("file", O_RDONLY);
  assert(fd >= 0);

  printf("fd: %d\n", fd);

  char c;
  assert(read(fd, &c, sizeof(char)) == 1);

  printf("Read: %c\n", c);

  pid_t ret = fork();

  if (ret == 0) {
    // Child
    assert(read(fd, &c, sizeof(char)) == 1);
    printf("Child read: %c\n", c);
    close(fd);
  } else {
    // Parent
    assert(read(fd, &c, sizeof(char)) == 1);
    printf("Parent read: %c\n", c);
    close(fd);

    // Wait for child.
    waitpid(ret, NULL, 0);
  }
}
