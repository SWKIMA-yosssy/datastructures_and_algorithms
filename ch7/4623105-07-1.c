#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define maxM 20

struct cell {
  int key;
  int next;
};

void bucket_sort(int *A, int n, int l, int u, int m);

int main(void) {
  int Data[maxN];
  int N, l, u, m;
  int i, j;
  int data_buf;
  int avoid_count = 0;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d %d %d %d", &N, &l, &u, &m);
  if (N > maxN) {
    printf("N is too large, setting N = %d\n", maxN);
    N = maxN;
  }

  for (i = 0; i < (N - avoid_count); i++) {
    printf("i: %d N-avoid_count: %d\n", i, N - avoid_count);
    fscanf(fp, "%d", &data_buf);
    if (data_buf < l || u < data_buf) {
      printf("%d is out of range from [%d %d]\n", data_buf, l, u);
      avoid_count++;
      i = i - 1;
    } else {
      Data[i] = data_buf;
    }
  }
  fclose(fp);

  for (i = 0; i < (N - avoid_count); i++) {
    printf("Data[%d] = %d [%d %d]\n", i, Data[i], l, u);
  }

  return 0;
}
