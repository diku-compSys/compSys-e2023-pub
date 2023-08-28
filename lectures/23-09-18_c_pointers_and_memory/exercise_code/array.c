#include <stdio.h>
#include <stdlib.h>

int update (int *arr, int size);

#define SIZE 10

int main() {
  int x[SIZE];

  // Initialize array
  for (int c = 0 ; c < SIZE ; c++) {
    x[c] = c * 2;
  }

  // Do some random updates to an array
  update((int*) &x, SIZE);

  // Print the elements
  for (int c = 0 ; c < SIZE ; c++) {
    printf("%d\n", x[c]);
  }

  return EXIT_SUCCESS;
}

int update (int *arr, int size) {
  for (int i = 0 ; i < size ; i++) {
    arr[i] += i;
    update(arr+i, size-1);
  }
  return 1;
}
