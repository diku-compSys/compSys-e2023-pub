#include <stdio.h>

int main() {
  int a[10] = { 1,2,3,4,5,6,7,8,9,10 };

  //  for (int i; i < 10; i++) {
  //    printf("&a[%d] = %p\n", i, &a[i]);
  //    printf("a[%d] = %d\n", i, a[i]);
  //  }

  int *p = &a[0];
  printf("p: %p\n", (void*)p);
  printf("*p: %d\n", *p);

  for (int i = 0; i < 10; i++) {
    printf("p: %p\n", (void*)p);
    printf("*p: %d\n", *p);
    p = p + 1; // implicit * sizeof(int)
  }
}
