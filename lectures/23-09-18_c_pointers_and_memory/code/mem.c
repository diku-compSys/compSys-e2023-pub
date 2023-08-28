#include <stdio.h>

int main() {
  int x = 2;
  printf("x: %d\n", x);
  printf("&x: %p\n", (void*)&x);

  int *px = &x;

  printf("px: %p\n", (void*)px);
  printf("&px: %p\n", (void*)&px);

  *px = 3;

  printf("x: %d\n", x);
  printf("&x: %p\n", (void*)&x);
}
