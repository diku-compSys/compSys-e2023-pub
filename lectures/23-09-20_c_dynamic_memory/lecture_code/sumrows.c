double sumvec(int n, const double *vector) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += vector[i];
  }
  return sum;
}

void sumrows(int n, int m,
             const double *matrix, double *vector) {
  for (int i = 0; i < n; i++) {
    vector[i] = sumvec(m, &matrix[i*m]);
  }
}

int main() {
}
