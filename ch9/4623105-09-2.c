#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000 // set infinity as number large enough

int Adj[maxN][maxN];
void make_adj_matrix(int start, int end);
void enqueue(int *Q, int *head, int *tail, int a);
int dequeue(int *Q, int *head, int *tail);
void bfs(int N, int *d, int *p, int *color, int v0, int *head, int *tail,
         int *Q);

int main(void) {
  int N, M;                          // N=number of node, M= number of edge
  int i, j;                          // counter
  int u, v;                          // temporary buffer
  int d[maxN], p[maxN], color[maxN]; // white = 0, gray =1, black = 2
  int v0;
  int Q[maxN];
  int head, tail;

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

  return 0;
}

void make_adj_matrix(int start, int end) {
  // adj matrix must be global variable
  Adj[start][end] = 1;
  Adj[end][start] = 1;
}

void enqueue(int *Q, int *head, int *tail, int a) {
  Q[*tail] = a;
  *tail = *tail + 1;
  if (*tail > maxN) {
    *tail = 0;
  }
  if (*tail == *head) {
    fprintf(stderr, "Error: Queue Overflow\n");
    exit(2);
  }
}

int dequeue(int *Q, int *head, int *tail) {
  int a;
  if (*head == *tail) {
    fprintf(stderr, "Error: Queue Underflow\n");
    exit(3);
  } else {
    a = Q[*head];
    *head = *head + 1;
    if (*head == maxN) {
      *head = 0;
    }
    return a;
  }
}

void bfs(int N, int *d, int *p, int *color, int v0, int *head, int *tail,
         int *Q) {
  int i;
  int v;

  // initialize
  for (i = 0; i < N; i++) {
    color[i] = 0;
    d[i] = inf;
    p[i] = -1; // NIL = -1
  }
  *head = 0;
  *tail = 0;

  enqueue(Q, head, tail, v0);

  while (*head != *tail) {
    v = dequeue(Q, head, tail);
    for (i = 0; i < N; i++) {
      if (Adj[v][i] == 1) {
        if (color[i] == 0) {
          enqueue(Q, head, tail, i);
          color[i] = 1;
          d[i] = d[v] + 1;
          p[i] = v;
        }
      }
    }
    color[v] = 2;
  }
}
