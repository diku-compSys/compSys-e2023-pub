#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {
  printf("1\n");
  pid_t pid = fork();
  if (pid == 0) {
    printf("2\n");
  } else {
    if (fork() == 0) {
      printf("3\n");
    } else {
      printf("4\n");
    }
  }
  printf("5\n");
}
