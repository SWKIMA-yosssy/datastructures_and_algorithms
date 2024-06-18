#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000 // set infinity as number large enough

int N, M; // N=number of node, M= number of edge
int Adj[maxN][maxN];
int d[maxN], f[maxN], p[maxN], color[maxN]; // white = 0, gray =1, black = 2
int T;

void make_adj_matrix(int start, int end);
void dfs(int v0);
void traverse(int v);

int main(void) {
  int i, j; // counter
  int u, v; // temporary buffer
  int v0;

  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);
  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);
  if (N > maxN) {
    fprintf(stderr, "Erorr:Too many data, number of data must not exceed %d\n",
            maxN);
    exit(1);
  }

  for (i = 0; i < N; i++) { // initialize of adjacency matrix
    for (j = 0; j < N; j++) {
      Adj[i][j] = 0;
    }
  }

  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d", &u, &v);
    make_adj_matrix(u, v);
  }
  fscanf(fp, " %d", &v0);
  fclose(fp);
  printf("Adjacency matrix\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d ", Adj[i][j]);
    }
    printf("\n");
  } // done initialize v0, N, M,and adj matrix

  dfs(v0);
  for (i = 0; i < N; i++) {
    printf("vertex %d: d[%d] = %d, f[%d] = %d, p[%d] = %d\n", i, i, d[i], i,
           f[i], i, p[i]);
  }
  return 0;
}

void make_adj_matrix(int start, int end) {
  // adj matrix must be global variable
  Adj[start][end] = 1;
  Adj[end][start] = 1;
}

void dfs(int v0) {
  int i;
  for (i = 0; i < N; i++) { // initialize all node's attribute
    color[i] = 0;
    d[i] = inf;
    f[i] = inf;
    p[i] = -1;
  }
  T = 0;
  traverse(v0);
}
void traverse(int v) {
  int i;

  color[v] = 1;
  T++;
  d[v] = T;

  for (i = 0; i < N; i++) {
    if (Adj[v][i] == 1) {
      if (color[i] == 0) {
        p[i] = v;
        traverse(i);
      }
    }
  }
  color[v] = 2;
  T++;
  f[v] = T;
}
