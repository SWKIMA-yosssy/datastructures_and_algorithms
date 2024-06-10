#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

void quicksort(int *A, int p, int r);
int partition(int *A, int p, int r);

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
  quicksort(Data, 0, N - 1);

  for (i = 0; i < N; i++) {
    printf("No.%d : %d\n", i, Data[i]);
  }
  return 0;
}

void quicksort(int *A, int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);
    quicksort(A, p, q);
    quicksort(A, q + 1, r);
  }
}
int partition(int *A, int p, int r) {
  int x = A[p];
  int i = p;
  int j = r;
  int buf;
  while (1) {
    while (A[j] <= x) {
      j++;
    }
    while (A[i] >= x) {
      i++;
    }
    if (i < j) {
      buf = A[i];
      A[i] = A[j];
      A[j] = buf;
    } else {
      break;
    }
  }
  return j;
}
