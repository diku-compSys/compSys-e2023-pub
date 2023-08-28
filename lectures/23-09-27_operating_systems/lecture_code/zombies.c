#include <unistd.h>
#include <stdio.h>

int main() {
  int num_children = 10;

  for (int i = 0; i < num_children; i++) {
    if (fork() == 0) {
      // In child.
      while (1);
    }
  }

  return 0; // Parent terminates.
}
