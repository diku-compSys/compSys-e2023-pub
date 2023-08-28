#include <stdio.h>
#include <stdlib.h>

int main() {
  for (int i = 1; i < 30000000; i++) {
    int num_bytes = 64;
    printf("malloc(%d) = %p\n", num_bytes, malloc(num_bytes));
  }
}
