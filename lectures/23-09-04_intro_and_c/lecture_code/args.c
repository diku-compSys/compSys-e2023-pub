#include <stdio.h>

int main(int argc, char* argv[]) {
  printf("argc: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    char* arg = argv[i];
    printf("%s", arg);
    printf("\n");
  }
}
