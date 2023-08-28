#include <stdlib.h>

int memeq(unsigned char *p1, unsigned char *p2, int n) {
  for (int i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return 0;
    }
  }
  return 1;
}

unsigned char* memfind(unsigned char *haystack, int haystacklen,
                       unsigned char *needle, int needlelen) {
  for (int i = 0; i < haystacklen-needlelen; i++) {
    if (memeq(haystack+i,needle,needlelen)) {
      return haystack+i;
    }
  }
  return NULL;
}

int stalinsort(int *array, int n) {
  if (n == 0) {
    return 0;
  }

  int prev = array[0];
  int i = 1;
  for (int j = 1; j < n; j++) {
    if (prev <= array[j]) {
      prev = array[j];
      array[i] = prev;
      i++;
    }
  }
  return i;
}
