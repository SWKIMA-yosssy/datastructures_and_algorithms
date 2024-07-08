#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define maxM 500

struct edge_data {
  int end1;
  int end2;
};

void make_set(int *p, int *rank, int x);
int find_set(int *p, int *rank, int x);
void set_union(int *p, int *rank, int x, int y);
void link(int *p, int *rank, int x, int y);

int main(void) {
  int N, M;
  struct edge_data edge[maxM];
  int p[maxN], rank[maxN];
  int component[maxN];
  int number_comp = 0;
  int i, j;
  int u, v;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
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
    fscanf(fp, " %d %d", &u, &v);
    edge[i].end1 = u;
    edge[i].end2 = v;
  }
  fclose(fp);

  for (u = 0; u < N; u++) {
    make_set(p, rank, u);
  }
  for (i = 0; i < M; i++) {
    set_union(p, rank, edge[i].end1, edge[i].end2);
  }

  for (i = 0; i < N; i++) {
    if (p[i] == i) {
      number_comp++;
      component[i] = number_comp;
    }
  }
  for (i = 0; i < N; i++) {
    component[i] = component[p[i]];
  }

  printf("number of components = %d\n", number_comp);
  for (i = 0; i < N; i++) {
    printf("vertex%d  component=%d  parent=%d  rank=%d\n", i, component[i],
           p[i], rank[i]);
  }
  return 0;
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

void set_union(int *p, int *rank, int x, int y) {
  int u = find_set(p, rank, x);
  int v = find_set(p, rank, y);
  if (u != v) {
    link(p, rank, u, v);
  }
}
