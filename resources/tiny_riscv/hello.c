#include "lib.h"

char m[] = "Hello from RISC-V\n";

int main() {
  char* p = m;
  while (*p) { outp(*p++); };
}

