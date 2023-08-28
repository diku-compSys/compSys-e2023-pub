#include <stdlib.h>
#include <stdio.h>

int main() {
  int size = 10;
  int *arr = malloc(size * sizeof(int));

  printf("&arr: %p\n", (void*)&arr);
  printf("arr:  %p\n", (void*)arr);

  for (int i = 0; i < size; i++) {
    arr[i] = i*2;
    printf("&arr[%d]: %p ", i, (void*)&arr[i]);
    printf("arr[%d]: %d\n", i, arr[i]);
  }

  free(arr);
}
