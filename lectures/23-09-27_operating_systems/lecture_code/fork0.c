#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void) {
  pid_t ret = fork();

  if (ret == 0) {
    // Child
    pid_t my_pid = getpid();
    printf("Child: ret=%d; my_pid=%d\n", (int)ret, (int)my_pid);
  } else {
    // Parent
    pid_t my_pid = getpid();
    printf("Parent: ret=%d; my_pid=%d\n", (int)ret, (int)my_pid);
  }
}
