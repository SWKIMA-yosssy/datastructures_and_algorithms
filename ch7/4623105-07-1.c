#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define maxM 20

struct cell {
  int key;
  int next;
};

void bucket_sort(int *A, int n, int l, int u, int m);
void insertion_sort(struct cell *L, int *n);

int main(void) {
  int Data[maxN];
  int N, l, u, m;
  int i, j;
  int data_buf;
  int avoid_count = 0;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d %d %d %d", &N, &l, &u, &m);
  if (N > maxN) {
    printf("N is too large, setting N = %d\n", maxN);
    N = maxN;
  }

  for (i = 0; i < (N - avoid_count); i++) {
    fscanf(fp, "%d", &data_buf);
    if (data_buf < l || u < data_buf) {
      printf("%d is out of range from [%d %d]\n", data_buf, l, u);
      avoid_count++;
      i = i - 1;
    } else {
      Data[i] = data_buf;
    }
  }
  fclose(fp);

  if (m > maxM) {
    printf("number of buckets m is too large, setting m = %d\n", maxN);
    m = maxM;
  }

  for (i = 0; i < N - avoid_count; i++) {
    printf("Data[%d] = %d\n", i, Data[i]);
  }

  bucket_sort(Data, N - avoid_count, l, u, m);

  printf("###after sort###\n");
  for (i = 0; i < N - avoid_count; i++) {
    printf("Data[%d] = %d\n", i, Data[i]);
  }
  return 0;
}

void bucket_sort(int *A, int n, int l, int u, int m) {
  struct cell List[maxN];
  int B[maxN];
  int i, j, k;

  for (i = 0; i < n; i++) {
    List[i].key = A[i];
    List[i].next = -1;
  }
  for (j = 0; j < m; j++) {
    B[j] = -1;
  }

  for (i = 0; i < n; i++) {
    if (A[i] != u) {
      List[i].next = B[m * A[i] / (u - l)];
      B[m * A[i] / (u - l)] = i;
    } else { // if A[i] == max range of bucket
      List[i].next = B[m * A[i] / (u - l) - 1];
      B[m * A[i] / (u - l) - 1] = i;
    }
  }

  for (j = 0; j < m; j++) {
    insertion_sort(List, &B[j]);
  }

  i = 0;
  for (j = 0; j < m; j++) {
    k = B[j];
    while (k != -1) {
      A[i] = List[k].key;
      i++;
      k = List[k].next;
    }
  }
}
void insertion_sort(struct cell *L, int *n) {
  int sorted = *n;
  int unsorted = L[*n].next;
  L[*n].next = -1;

  while (unsorted != -1) {
    int current = unsorted;
    unsorted = L[unsorted].next;

    if (L[current].key < L[sorted].key) {
      L[current].next = sorted;
      sorted = current;
    } else {
      int p = sorted;
      while (L[p].next != -1 && L[L[p].next].key < L[current].key) {
        p = L[p].next;
      }
      L[current].next = L[p].next;
      L[p].next = current;
    }
  }

  *n = sorted;
}
