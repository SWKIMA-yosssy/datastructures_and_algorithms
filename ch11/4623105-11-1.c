#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000

int main(void) {
  int N, M;
  int Lmat[maxN + 1][maxN + 1];
  int d[maxN + 1][maxN + 1][maxN + 1];
  int i, j, k;
  int u, v;
  int len;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);
  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);
  if (N > maxN) {
    fprintf(stderr, "Erorr: N>maxN, redefine maxN\n");
    exit(1);
  }

  for (i = 1; i <= N; i++) { // initialize Lmat
    for (j = 1; j <= N; j++) {
      if (i != j) {
        Lmat[i][j] = inf;
      } else {
        Lmat[i][j] = 0;
      }
    }
  }
  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d %d", &u, &v, &len);
    Lmat[u][v] = len;
    Lmat[v][u] = len;
  }
  fclose(fp);

  k = 0;
  for (u = 1; u <= N; u++) {
    for (v = 1; v <= N; v++) {
      d[k][u][v] = Lmat[u][v];
    }
  }

  printf("k=%d\n", k);
  for (u = 1; u <= N; u++) {
    printf(" %2d:", u);
    if (u > 1) {
      for (v = 1; v < u; v++) {
        printf("   ");
      }
    }
    for (v = u; v <= N; v++) {
      if (d[k][u][v] != inf) {
        printf(" %2d", d[k][u][v]);
      } else {
        printf(" --");
      }
    }
    printf("\n");
  }

  for (k = 1; k <= N; k++) {
    for (i = 1; i <= N; i++) {
      d[k][i][i] = 0;
      for (j = i; j <= N; j++) {
        if (i > k) {
          d[k - 1][i][k] = d[k - 1][k][i];
        }
        if (k > j) {
          d[k - 1][k][j] = d[k - 1][j][k];
        }
        if (d[k - 1][i][k] + d[k - 1][k][j] < d[k - 1][i][j]) {
          d[k][i][j] = d[k - 1][i][k] + d[k - 1][k][j];
        } else {
          d[k][i][j] = d[k - 1][i][j];
        }
      }
    }

    printf("k=%d\n", k);
    for (u = 1; u <= N; u++) {
      printf(" %2d:", u);
      if (u > 1) {
        for (v = 1; v < u; v++) {
          printf("   ");
        }
      }
      for (v = u; v <= N; v++) {
        if (d[k][u][v] != inf) {
          printf(" %2d", d[k][u][v]);
        } else {
          printf(" --");
        }
      }
      printf("\n");
    }
  }
  return 0;
}
