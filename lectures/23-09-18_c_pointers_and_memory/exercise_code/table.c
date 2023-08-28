#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 1000
#define WIDTH 10

int updateElement (int* table, int row, int col, int value);

int main() {
  int table[HEIGHT][WIDTH];

  for (int h = 0 ; h < HEIGHT ; h++) {
    for (int w = 0 ; w < WIDTH ; w++) {
      table[w*h][h] = w*h;
    }
  }

  // print table[5][5]
  printf("Element 5,5: %d\n", table[5][5]);
  return EXIT_SUCCESS;
}
