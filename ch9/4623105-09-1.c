#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

int Adj[maxN][maxN];
void make_adj_matrix(int start, int end);

int main(void) {
  int N, M; // N=number of node, M= number of edge
  int i, j; // counter
  int u, v; // temporary buffer
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
  fclose(fp);
  printf("Adjacency matrix\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d ", Adj[i][j]);
    }
    printf("\n");
  }

  return 0;
}

void make_adj_matrix(int start, int end) {
  // adj matrix must be global variable
  Adj[start][end] = 1;
  Adj[end][start] = 1;
}
