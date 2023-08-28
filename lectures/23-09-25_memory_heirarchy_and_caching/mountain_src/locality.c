#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

#define BYTES (1<<30)
#define MAXELEMS ((int)(BYTES/sizeof(int)))

int data[MAXELEMS];  // Global array to traverse

// Iterate over first "elems" elements of array “data” with stride of
// "stride", using 4x4 loop unrolling.
void test(int limit, int stride) {
  long acc = 0;
  int stridex4 = stride*4;

  // Access data with a stride.  Loop is unrolled to prevent the C
  // compiler optimiser from messing unpredictably with it.
  for (int i = 0; i < limit-stridex4; i += stridex4) {
    acc = acc + data[i];
    acc = acc + data[i+1*stride];
    acc = acc + data[i+2*stride];
    acc = acc + data[i+3*stride];
  }

  // Avoid the optimiser removing the computation.
  data[0] = acc;
}

double test_MiB(int limit, int stride) {
  // TODO
}

double test_time(int limit, int stride) {
  // TODO
}

int main() {
  // Initialise the data so that an eager C compiler will not be able
  // to figure out that we are adding together zeroes.
  for (int i = 0; i < MAXELEMS; i++) {
    data[i] = i;
  }

  // TODO
}
