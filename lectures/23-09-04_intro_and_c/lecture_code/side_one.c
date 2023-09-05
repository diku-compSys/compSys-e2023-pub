#include <stdio.h>

// Note this is not something to copy
int main(void) {
  int a = 3;
  int b = 5;
  int c = a++ + ++b;

  printf("a = %d\n", a);
  printf("b = %d\n", b);
  printf("c = %d\n", c);
}