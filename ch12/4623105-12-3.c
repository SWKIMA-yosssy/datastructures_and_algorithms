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
void kruskal(int n, int m, struct edge_data *edge, int *p, int *rank,
             int *ednum, int *T);

int main(void) {
  int N, M;
  struct edge_data edge[maxM];
  int W[maxM];
  int p[maxN];
  int rank[maxN];
  int ednum[maxM];
  int T[maxM];
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
  kruskal(N, M, edge, p, rank, ednum, T);
  for (i = 0; i < M; i++) {
    if (T[i] == 1) {
      printf("edge (%d, %d)  weight = %d\n", edge[i].end1, edge[i].end2,
             edge[i].weight);
    }
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
    while (A[j] > x) {
      j--;
    }
    while (A[i] < x) {
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
void make_set(int *p, int *rank, int x) {
  p[x] = x;
  rank[x] = 0;
}

int find_set(int *p, int *rank, int x) {
  int y = x;
  int z;
  while (y != p[y]) {
    y = p[y];
  }
  int r = y;
  y = x;
  while (y != r) {
    z = p[y];
    p[y] = r;
    y = z;
  }

  return r;
}

void link(int *p, int *rank, int x, int y) {
  if (rank[x] > rank[y]) {
    p[y] = x;
  } else {
    p[x] = y;
    if (rank[x] == rank[y]) {
      rank[y] = rank[y] + 1;
    }
  }
}

int set_union(int *p, int *rank, int x, int y) {
  int u = find_set(p, rank, x);
  int v = find_set(p, rank, y);
  if (u != v) {
    link(p, rank, u, v);
    return 1;
  }
  return 0;
}

void kruskal(int n, int m, struct edge_data *edge, int *p, int *rank,
             int *ednum, int *T) {
  int i;
  int u, v;
  for (i = 0; i < m; i++) {
    T[i] = 0;
  }
  for (u = 0; u < n; u++) {
    make_set(p, rank, u);
  }
  for (i = 1; i < m; i++) {
    u = edge[ednum[i]].end1;
    v = edge[ednum[i]].end2;
    T[i] = set_union(p, rank, u, v);
  }
}
