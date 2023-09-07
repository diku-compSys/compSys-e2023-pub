
asm("  .globl _start");
asm("_start:");
asm("  li sp, 0x1000000");
asm("  call main");
asm("  call terminate");

extern int main();


char inp() {
  char c;
  asm("  addi a7,x0,1");
  asm("  ecall");
  asm("  add %0,x0,a7" : "=r" (c));
  return c;
}

void outp(char c) {
  asm("  addi a7,x0,2");
  asm("  add  a6,x0,%0" : : "r" (c));
  asm("  ecall");
}

void terminate() {
  asm("  addi a7,x0,3");
  asm("  ecall");
  // never returns (stops machine)
}

void print_string(const char* p) {
  while (*p) { outp(*p++); };
}

void read_string(char* buffer, int max_chars) {
  int c = inp();
  while (c != '\n' && c != '\r' && max_chars > 1) {
    *buffer++ = c;
    --max_chars;
    c = inp();
  }
  // zero terminate:
  *buffer = 0;
}



unsigned int str_to_uns(const char* str) {
  unsigned int val = *str++ - '0';
  while (*str) {
    val = val * 10 + *str++ - '0';
  }
  return val;
}

int uns_to_str(char* buffer, unsigned int val) {
  if (val == 0) {
    buffer[0] = '0';
    buffer[1] = 0;
    return 1;
  }
  // produce digits in reverse order
  char* ptr = buffer;
  while (val) {
    *ptr++ = (val % 10) + '0';
    val = val / 10;
  }
  *ptr-- = 0;
  int retval = ptr - buffer;
  // reverse
  while (ptr > buffer) {
    char tmp = *ptr;
    *ptr = *buffer;
    *buffer = tmp;
    --ptr;
    ++buffer;
  }
  return retval;
}
