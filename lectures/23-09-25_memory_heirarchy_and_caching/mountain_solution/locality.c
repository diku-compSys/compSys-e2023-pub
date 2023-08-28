#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

// Get the number of (fractional) seconds since 1st of January, 1970 -
// the "Unix epoch".
double seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL); // The null is for timezone information.
  return tv.tv_sec + tv.tv_usec/1000000.0;
}

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
  double elems = ((double)limit)/stride;
  double bytes = elems*sizeof(int);
  double MiB = bytes/(1024*1024);
  return MiB;
}

double test_time(int limit, int stride) {
  int runs = 10;

  test(limit, stride); // Warmup.
  double bef = seconds();
  for (int i = 0; i < runs; i++) {
    test(limit, stride); // Timing run.
  }
  double aft = seconds();
  double elapsed = aft - bef;
  double MiB = test_MiB(limit, stride)*runs;
  return MiB/elapsed;
}

int main() {
  // Initialise the data so that an eager C compiler will not be able
  // to figure out that we are adding together zeroes.
  for (int i = 0; i < MAXELEMS; i++) {
    data[i] = i;
  }

  for (int i = 13; i < 28; i++) {
    int limit = 2<<i;
    assert(limit <= MAXELEMS);
    for (int stride = 1; stride < 12; stride++) {
      double MiB_per_sec = test_time(limit, stride);
      int bytes = limit*sizeof(int);
      printf("%d %d %.1f\n", stride, bytes, MiB_per_sec);
    }
    printf("\n");
  }
}
