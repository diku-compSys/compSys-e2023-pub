#include "lib.h"

#define MAX 1000000



void main() {
  // init
  char numbers[MAX];
  for (int i = 0; i < MAX; ++i) numbers[i] = 1;
  print_string("Primtal: 1 ");
  for (int i = 2; i < MAX; ++i) {
    if (numbers[i]) {
      char buf[20];
      uns_to_str(buf, i);
      print_string(buf);
      print_string(" ");
      for (int j = i; j < MAX; j += i) numbers[j] = 0;
    }
  }
  print_string("\n");
}
