#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

void mergesort(int *A, int p, int r);
void merge(int *A, int p, int q, int r);

int main(void) {
  int Data[maxN];
  int N;
  int i, j;

  char fname[128];
  FILE *fp;
  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);
  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > maxN) {
    printf("Too many data, number of data must not exceed %d\n", maxN);
    printf("Sorting first %d values \n", maxN);
    N = maxN;
  }

  for (i = 0; i < N; i++) {
    fscanf(fp, "%d", &Data[i]);
  }
  fclose(fp);

  for (i = 0; i < N; i++) {
    printf("No.%d : %d\n", i, Data[i]);
  }
  mergesort(Data, 0, N - 1);

  printf("### exec sort ###\n");
  for (i = 0; i < N; i++) {
    printf("No.%d : %d\n", i, Data[i]);
  }
  return 0;
}

void mergesort(int *A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    mergesort(A, p, q);
    mergesort(A, q + 1, r);
    merge(A, p, q, r);
  }
}

void merge(int *A, int p, int q, int r) {
  int B[maxN];
  int i = p;
  int j = q + 1;
  int k = p;
  int counter = 0;

  while (1) {
    if (A[i] <= A[j]) {
      B[k] = A[i];
      i++;
    } else {
      B[k] = A[j];
      j++;
    }
    k++;
    if (i > q || j > r) {
      break;
    }
  }

  if (i <= q) {
    while (i <= q) {
      B[k] = A[i];
      i++;
      k++;
    }
  } else if (j <= r) {
    while (j <= r) {
      B[k] = A[j];
      j++;
      k++;
    }
  }

  for (counter = p; counter <= r; counter++) {
    A[counter] = B[counter];
  }
}
