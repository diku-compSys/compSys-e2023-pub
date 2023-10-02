#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
  pid_t ret = fork();

  if (ret == 0) {
    // Child
    pid_t my_pid = getpid();
    printf("Child: ret=%d; my_pid=%d\n", (int)ret, (int)my_pid);
//    *((int*)NULL) = 0;
    exit(42);
  } else {
    // Parent

    // Wait for child.
    int wstatus;
    waitpid(ret, &wstatus, 0);

    pid_t my_pid = getpid();
    printf("Parent: ret=%d; my_pid=%d\n", (int)ret, (int)my_pid);

    if (WIFSIGNALED(wstatus)) {
      printf("Child was killed by signal %d\n", WTERMSIG(wstatus));
    } else {
      printf("Child returned %d\n", WEXITSTATUS(wstatus));
    }
  }
}
