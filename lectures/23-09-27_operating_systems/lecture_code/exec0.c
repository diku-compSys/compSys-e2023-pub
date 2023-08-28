#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  pid_t ret = fork();

  if (ret == 0) {
    // Child
    exit(execvp(argv[1], argv+1));
  } else {
    // Parent
    int wstatus;
    waitpid(ret, &wstatus, 0);

    return WEXITSTATUS(wstatus);
  }
}
