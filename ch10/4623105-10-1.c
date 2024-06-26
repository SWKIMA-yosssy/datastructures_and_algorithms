#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000

int G[maxN][maxN];

void dijkstra(int G[maxN][maxN], int d[maxN], int p[maxN], int A[maxN], int N);

int main(void) {
  int i, j;
  int d[maxN];
  int p[maxN];
  int A[maxN];
  int v0;
  int u, v, weight;
  int N, M;
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
    d[i] = inf;
    p[i] = -1;
    A[i] = 0;
    for (j = 0; j < N; j++) {
      G[i][j] = inf;
    }
  }

  for (i = 0; i < M; i++) {
    fscanf(fp, "%d %d  %d", &u, &v, &weight);
    G[u][v] = weight;
    G[v][u] = weight;
  }
  fscanf(fp, "%d", &v0);
  fclose(fp);

  d[v0] = 0; // initialize and get Dijkstra start
  p[v0] = -1;
  A[v0] = 1;

  dijkstra(G, d, p, A, N);

  for (i = 0; i < N; i++) { // output outcome
    printf("vertex 0: d[%d] = %d, p[%d] = %d\n", i, d[i], i, p[i]);
  }
  return 0;
}

void dijkstra(int G[maxN][maxN], int d[maxN], int p[maxN], int A[maxN], int N) {
  int mind = inf;       // node which is minimam in A
  int v = -1;           // = v; buffer which remember node which is minimam in A
  int flag_A_empty = 1; // 0 = A is empty, 1 = A is not empty
  int w;
  int i;

  while (flag_A_empty > 0) {
    for (i = 0; i < N; i++) {
      if (A[i] == 1) {
        mind = d[i];
        v = i;
      }
    }
    A[v] = 0; // delete node which has minimam d among A

    for (i = 0; i < N; i++) {
      if (G[v][i] != inf) {
        w = i;
        if (d[w] == inf) {
          d[w] = d[v] + G[v][w];
          p[w] = v;
        } else if (d[w] > d[v] + G[v][w]) {
          d[w] = d[v] + G[v][w];
          p[w] = v;
        }
      }
    }

    // check whether A is empty or not
    flag_A_empty = 0;
    for (i = 0; i < N; i++) {
      if (A[i] == 1) {
        flag_A_empty++;
      }
    }
  }
}
