#include "lib.h"

int main(int argc, const char* argv[]) {
  char buffer[128];
  print_string("Hej med dig - skriv noget, saa bliver jeg glad: ");
  read_string(buffer, 128);
  print_string("Du skrev: ");
  print_string(buffer);
  return 0;
}

