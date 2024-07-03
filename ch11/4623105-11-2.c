#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000

int main(void) {
  int N;
  int p[maxN + 1];
  int m[maxN + 1][maxN + 1], s[maxN + 1][maxN + 1];
  int i, j, l, k;
  int buf_min;

  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);
  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > maxN) {
    fprintf(stderr, "Erorr: N>maxN, redefine maxN\n");
    exit(1);
  }

  for (i = 1; i <= N; i++) { // initialize Lmat
    fscanf(fp, " %d", &p[i]);
  }
  fclose(fp);
  for (i = 0; i < N; i++) {
    printf("matrix %2d:(%d, %d)\n", i, p[i - 1], p[i]);
  }

  for (i = 1; i <= N; i++) {
    m[i][i] = 0;
  }
  for (l = 2; l <= N; l++) {
    for (i = 1; i <= N - l + 1; i++) {
      j = i + l - 1;
      buf_min = inf;
      for (k = i; k <= j - 1; k++) {
        if (buf_min > m[j][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]) {
          buf_min = m[j][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
          s[i][j] = k;
        }
      }
      m[i][j] = buf_min;
    }
  }

  printf("m-values:\n");
  for (i = 1; i <= N; i++) {
    printf(" %2d", i);
    for (j = 1; j <= i; j++) {
      printf("   ");
    }
    for (j = i + 1; j <= N; j++) {
      printf(" %2d", s[i][j]);
    }
    printf("\n");
  }

  return 0;
}
