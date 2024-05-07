#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

struct cell {
  int key;
  int prev;
  int next;
};

int allocate_object(struct cell *L, int *f);

int main(void) {
  struct cell List[maxN];
  int N;
  int Data[maxN];
  int i;
  int head, freeL;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname) - 1] = '\0';
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > maxN) {
    printf("N is too large, setting N = %d\n", maxN);
    N = maxN;
  }
  for (i = 0; i < N; i++) {
    fscanf(fp, "%d", &Data[i]);
  }
  fclose(fp);

  for (i = 0; i < maxN - 1; i++) {
    List[i].next = i + 1;
  }
  List[maxN - 1].next = -1;
  head = -1;
  freeL = 0;

  return 0;
}
