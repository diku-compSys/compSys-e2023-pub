#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

int main(int argc, char** argv) {
  (void)argc;

  pid_t ret = fork();

  if (ret == 0) {
    // Child
    FILE* out = fopen("output", "w");
    assert(dup2(fileno(out), 1) == 1);
    exit(execvp(argv[1], argv+1));
  } else {
    // Parent
    int wstatus;
    waitpid(ret, &wstatus, 0);

    return WEXITSTATUS(wstatus);
  }
}
