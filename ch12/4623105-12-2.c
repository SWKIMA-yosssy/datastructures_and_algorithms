#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define maxM 500

struct edge_data {
  int end1;
  int end2;
  int weight;
};

void quicksort(int *A, int *ednum, int p, int r);
int partition(int *A, int *ednum, int p, int r);

int main(void) {
  int N, M;
  struct edge_data edge[maxM];
  int W[maxM];
  int ednum[maxM];
  int i, j;
  int u, v, w;
  char fname[128];
  FILE *fp;

  printf("input filename:");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);
  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);
  if (N > maxN || M > maxM) {
    fprintf(stderr, "N or M is too large, redefine maxN, maxM\n");
    exit(1);
  }

  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d %d", &u, &v, &w);
    edge[i].end1 = u;
    edge[i].end2 = v;
    edge[i].weight = w;
  }
  fclose(fp);

  for (i = 0; i < M; i++) {
    W[i] = edge[i].weight;
    ednum[i] = i;
  }

  quicksort(W, ednum, 0, M - 1);

  for (i = 0; i < M; i++) {
    printf("edge %2d: (%2d, %2d)", ednum[i], edge[ednum[i]].end1,
           edge[ednum[i]].end2);
    printf(" weight = %d\n", edge[ednum[i]].weight);
  }

  return 0;
}
void quicksort(int *A, int *ednum, int p, int r) {
  if (p < r) {
    int q = partition(A, ednum, p, r);
    quicksort(A, ednum, p, q - 1);
    quicksort(A, ednum, q + 1, r);
  }
}
int partition(int *A, int *ednum, int p, int r) {
  int x = A[p];
  int i = p;
  int j = r;
  int buf;
  while (1) {
    while (A[j] < x) {
      j--;
    }
    while (A[i] > x) {
      i++;
    }
    if (i < j) {
      buf = A[i];
      A[i] = A[j];
      A[j] = buf;
      buf = ednum[i];
      ednum[i] = ednum[j];
      ednum[j] = buf;
    } else {
      break;
    }
  }
  return j;
}
