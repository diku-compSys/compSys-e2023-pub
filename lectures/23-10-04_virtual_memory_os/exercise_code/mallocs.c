#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  for (int i = 1; i < 30; i++) {
    int num_bytes = 1 << i;
    printf("malloc(%d): ", num_bytes);
    printf("%p\n", malloc(num_bytes));
  }
}
