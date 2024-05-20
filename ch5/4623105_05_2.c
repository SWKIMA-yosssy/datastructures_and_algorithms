#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

int parent(int i);
void heapsort(int *H, int *A, int n);
void build_heap(int *H, int *A, int n);
void insert(int *H, int i, int a);
void upheap_sort(int *H, int i);
void downheap_sort(int *H, int i);
void increase_key(int *H, int i, int a);

int main(void) {
  int Data[maxN];
  int Heap[maxN];
  int N;
  int i;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > maxN) {
    printf("N is too large, setting N = %d\n", maxN);
    N = maxN;
  }
  for (i = 0; i < N; i++) {
    fscanf(fp, "%d", &Data[i]);
  }
  fclose(fp);

  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");

  heapsort(Heap, Data, N);

  for (i = 0; i < N; i++) {
    printf("%d ", Data[i]);
  }
  printf("\n");

  return 0;
}

int parent(int i) {
  int p;
  p = (i - 1) / 2;
  return p;
}
void upheap_sort(int *H, int i) {
  int u = i;
  int buf;
  while (u > 0 && H[parent(u)] < H[u]) {
    buf = H[parent(u)];
    H[parent(u)] = H[u];
    H[u] = buf;
    u = parent(u);
  }
}

void insert(int *H, int i, int a) {
  H[i] = a;
  upheap_sort(H, i);
}

void build_heap(int *H, int *A, int n) {
  int i;
  for (i = 0; i <= n - 1; i++) {
    insert(H, i, A[i]);
  }
}

void downheap_sort(int *H, int i) {
  int u = 0;
  int l;
  int r;
  int buf;
  int flag = 1; // 0:no change 1:change executed;
  while (flag == 1) {
    if (2 * u + 1 <= i) {
      l = 2 * u + 1;
    } else {
      l = u;
    }
    if (2 * u + 2 <= i) {
      r = 2 * u + 2;
    } else {
      r = u;
    }
    if (H[u] < H[l]) {
      if (H[l] < H[r]) {
        buf = H[u];
        H[u] = H[r];
        H[r] = buf;
        u = r;
      } else if (H[r] < H[l]) {
        buf = H[u];
        H[u] = H[l];
        H[l] = buf;
        u = l;
      }
    } else if (H[l] < H[u] && H[u] < H[r]) {
      buf = H[u];
      H[u] = H[r];
      H[r] = buf;
      u = r;
    } else {
      flag = 0;
    }
  }
}

void heapsort(int *H, int *A, int n) {
  int i;
  build_heap(H, A, n);
  for (i = 1; i <= n - 1; i++) {
    A[n - i] = H[0];
    H[0] = H[n - i];
    downheap_sort(H, n - i - 1);
  }
  A[0] = H[0];
}

void increase_key(int *H, int i, int a) {
  if (H[i] > a) {
    fprintf(stderr, "invalid a\n");
    exit(1);
  }
  H[i] = a;
  if (H[parent(i)] < H[i]) {
    upheap_sort(H, i);
  }
}
