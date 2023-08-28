#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int sum = 0;
  for (int i = 1; i < argc; i++) {
    int x;
    if (sscanf(argv[i], "%d", &x) == 1) {
      sum = sum + x;
    } else {
      printf("Not an integer: %s\n", argv[i]);
      return 1;
    }
  }
  printf("%d\n", sum);
}
