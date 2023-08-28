#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef void (*matmul_fn)(int n, double*, double*, double*);

const int runs = 50;

void test(int* ns, matmul_fn f) {
  while (*ns > 0) {
    int n = *ns;
    double *a = calloc(n*n, sizeof(double));
    double *b = calloc(n*n, sizeof(double));
    double *c = calloc(n*n, sizeof(double));
    struct timespec bef, aft;
    clock_gettime(CLOCK_MONOTONIC, &bef);
    for (int i = 0; i < runs; i++) {
      f(n, a, b, c);
    }
    clock_gettime(CLOCK_MONOTONIC, &aft);
    double bef_s = bef.tv_sec + bef.tv_nsec / 1000000000.0;
    double aft_s = aft.tv_sec + aft.tv_nsec / 1000000000.0;
    printf("%d: %f\n", n, (aft_s-bef_s)*1000.0);
    free(a);
    free(b);
    free(c);
    ns++;
  }
}

void ijk(int n, double a[n][n], double b[n][n], double c[n][n]) {
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      double sum = 0.0;
      for (int k=0; k<n; k++)
        sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

void kij(int n, double a[n][n], double b[n][n], double c[n][n]) {
for (int k=0; k<n; k++) {
  for (int i=0; i<n; i++) {
  double r = a[i][k];
  for (int j=0; j<n; j++)
    c[i][j] += r * b[k][j];
  }
}
}


void jki(int n, double a[n][n], double b[n][n], double c[n][n]) {
  for (int j=0; j<n; j++) {
    for (int k=0; k<n; k++) {
      double r = b[k][j];
      for (int i=0; i<n; i++)
        c[i][j] += a[i][k] * r;
    }
  }
}

void usage(char** argv) {
  fprintf(stderr, "Usage: %s <ijk|kij|jki>\n", argv[0]);
  exit(1);
}

int main(int argc, char** argv) {
  int ns[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 0};
  if (argc != 2) {
    usage(argv);
  } else if (strcmp(argv[1], "ijk") == 0) {
    test(ns, (matmul_fn)ijk);
  } else if (strcmp(argv[1], "kij") == 0) {
    test(ns, (matmul_fn)kij);
  } else if (strcmp(argv[1], "jki") == 0) {
    test(ns, (matmul_fn)jki);
  } else {
    usage(argv);
  }
}
