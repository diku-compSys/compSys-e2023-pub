#include <stdio.h>

int main(void) {
  FILE *f = fopen("output", "w");
  int x = 1337;            // Number to write;
  char s[10];              // Output buffer.
  int i = 10;              // Index of last character written.
  while (1) {
    int d = x % 10;        // Pick out last decimal digit.
    x = x / 10;            // Remove last digit.
    i = i - 1;             // Index of next character.
    s[i] = '0' + d;        // Save ASCII character for digit.
    if (x == 0) { break; } // Stop if all digits written.
  }
  fwrite(&s[i], sizeof(char), 10-i, f); // Write ASCII bytes.
  fclose(f);                            // Close output file.
}
