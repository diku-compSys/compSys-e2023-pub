#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>

int file_pipe(FILE* files[2]) {
  int fds[2];

  int r = pipe(fds);

  if (r == 0) {
    files[0] = fdopen(fds[0], "r");
    files[1] = fdopen(fds[1], "w");

    if (files[0] && files[1]) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return r;
  }
}

int main(void) {
  FILE* files[2];
  assert(file_pipe(files) == 0);
  FILE *read_end = files[0];
  FILE *write_end = files[1];

  pid_t ret = fork();

  if (ret == 0) {
    // Child
    pid_t my_pid = getpid();
    printf("Child: ret=%d; my_pid=%d\n", (int)ret, (int)my_pid);
    fprintf(write_end, "Hello parent!\n");
    fprintf(write_end, "I think I am PID %d!\n", my_pid);
  } else {
    // Parent
    pid_t my_pid = getpid();
    printf("Parent: ret=%d; my_pid=%d\n", (int)ret, (int)my_pid);

    // Remember to close the write end of the pipe, or else we will
    // never get EOFs from the fread() below.
    fclose(write_end);

    char c;
    while (fread(&c, sizeof(char), 1, read_end) == 1) {
      putchar(c);
      fflush(stdout);
    }
  }
}
