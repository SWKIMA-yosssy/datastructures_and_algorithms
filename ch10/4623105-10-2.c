#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000

struct cell {
  int key;
  int vertex;
};

int parent(int i);
int right(int i);
int left(int i);
void insert(struct cell *H, int *adr, int i, int a, int v);
void decrease_key(struct cell *H, int *adr, int i, int a);
int delete_min(struct cell *H, int *adr, int i);
void upheap_sort(struct cell *H, int *adr, int i);
void downheap_sort(struct cell *H, int *adr, int i);
void dijkstra(int G[maxN][maxN], struct cell *H, int d[maxN], int p[maxN],
              int A[maxN], int N, int *hsize);

int main(void) {
  int N, M;
  int Lmat[maxN][maxN];
  struct cell Heap[maxN];
  int adr[maxN];
  int d[maxN], p[maxN];
  int hsize;
  int v0;
  int len;
  int u, v;
  int i, j;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);
  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);
  if (N > maxN) {
    fprintf(stderr, "N > maxN, redefine maxN\n");
  }
  for (i = 0; i < N; i++) { // initialize Lmat
    for (j = 0; j < N; j++) {
      Lmat[i][j] = inf;
    }
  }

  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d  %d", &u, &v, &len);
    Lmat[u][v] = len;
  }
  fscanf(fp, "%d", &v0);
  fclose(fp);

  for (u = 0; u < N; u++) {
    d[u] = inf;
    p[u] = -1;
    adr[u] = -1;
  }
  d[v0] = 0; // initialize and get Dijkstra start
  p[v0] = -1;
  adr[v0] = v0;
  hsize = 0;
  hsize++;
  insert(Heap, adr, 0, d[v0], v0);

  dijkstra(Lmat, Heap, d, p, adr, N, &hsize);

  for (i = 0; i < N; i++) { // output outcome
    printf("vertex %d: d[%d] = %d, p[%d] = %d\n", i, i, d[i], i, p[i]);
  }
  return 0;
}

void dijkstra(int G[maxN][maxN], struct cell *H, int d[maxN], int p[maxN],
              int adr[maxN], int N, int *hsize) {
  int v;
  int w;
  int i;

  while (*hsize > 0) {

    v = delete_min(H, adr, *hsize); // delete node which has minimam d among A
    *hsize = *hsize - 1;
    for (i = 0; i < N; i++) {
      if (G[v][i] < inf) {
        w = i;
        if (d[w] == inf) {
          d[w] = d[v] + G[v][w];
          p[w] = v;
          *hsize = *hsize + 1;
          insert(H, adr, *hsize - 1, d[w], w);
        } else if (d[w] > d[v] + G[v][w]) {
          d[w] = d[v] + G[v][w];
          p[w] = v;
          decrease_key(H, adr, w, d[w]);
        }
      }
    }
  }
}

int parent(int i) { return (i - 1) / 2; }
int right(int i) { return 2 * i + 2; }
int left(int i) { return 2 * i + 1; }

void insert(struct cell *H, int *adr, int i, int a, int v) {
  H[i].key = a;
  H[i].vertex = v;
  adr[i] = v;
  upheap_sort(H, adr, i - 1);
}

int delete_min(struct cell *H, int *adr, int i) {
  int v = H[0].vertex;
  adr[v] = -1;
  if (i > 1) {
    H[0].key = H[i - 1].key;
    H[0].vertex = H[i - 1].vertex;
    adr[H[0].vertex] = 0;
    downheap_sort(H, adr, i - 2);
  }
  return v;
}
void decrease_key(struct cell *H, int *adr, int i, int a) {
  H[i].key = a;
  upheap_sort(H, adr, i - 1);
}
void upheap_sort(struct cell *H, int *adr, int i) {
  int u = i;
  int adr_buf;
  struct cell temp;
  while (u > 0 && H[parent(u)].key > H[u].key) {
    temp = H[parent(u)];
    H[parent(u)] = H[u];
    H[u] = temp;
    adr_buf = adr[u];
    adr[parent(u)] = adr[u];
    adr[u] = adr_buf;
    u = parent(u);
  }
}

void downheap_sort(struct cell *H, int *adr, int i) {
  int u = 0;
  int l;
  int r;
  struct cell temp;
  int adr_buf;
  int flag = 1; // 0:no change 1:change executed;
  while (flag == 1) {
    if (left(u) <= i) {
      l = left(u);
    } else {
      l = u;
    }
    if (right(u) <= i) {
      r = right(u);
    } else {
      r = u;
    }
    if (H[u].key > H[l].key) {
      if (H[l].key > H[r].key) {
        temp = H[u];
        H[u] = H[r];
        H[r] = temp;
        adr_buf = adr[u];
        adr[u] = adr[r];
        adr[r] = adr_buf;
        u = r;
      } else if (H[r].key > H[l].key) {
        temp = H[u];
        H[u] = H[l];
        H[l] = temp;
        adr_buf = adr[u];
        adr[u] = adr[l];
        adr[l] = adr_buf;
        u = l;
      }
    } else if (H[l].key > H[u].key && H[u].key > H[r].key) {
      temp = H[u];
      H[u] = H[r];
      H[r] = temp;
      adr_buf = adr[u];
      adr[u] = adr[r];
      adr[r] = adr_buf;
      u = r;
    } else {
      flag = 0;
    }
  }
}
