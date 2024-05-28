#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 20
#define m 97
#define maxN 50

struct cell {
  char key[W + 1];
  unsigned int state : 2; // 0:empty 1:occupied 2:deleted
};

int hash_search(struct cell *A, char *a);
void hash_insert(struct cell *A, char *a);
int hash_val(char *a);

int main(void) {
  struct cell A[m];
  int N;
  int i, h;
  char word[W + 1];
  char fname[128];
  FILE *fp;

  for (h = 0; h < m; h++) {
    A[h].state = 0;
  }

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
    fscanf(fp, "%s", word);
    if (hash_search(A, word) != -1) {
      hash_insert(A, word);
    }
  }
  fclose(fp);
  for (h = 0; h < m; h++) {
    if (A[h].state != 0) {
      printf("A[%d] = %s\n", h, A[h].key);
    }
  }

  return 0;
}

void hash_insert(struct cell *A, char *a) {
  int h = hash_val(a);
  int x = -1;
  int i = 0;
  while (x == -1 && i < m) {
    if (A[(h + i) % m].state != 1) {
      x = (h + i) % m;
    } else {
      i++;
    }
  }

  if (x == -1) {
    printf("error: out of space");
  } else {
    strcpy(A[x].key, a);
    A[x].state = 1;
  }
}

int hash_val(char *a) {
  int h, i;

  h = 0;
  i = 0;
  while (a[i] != 0 && i < W) {
    h = h + (int)a[i];
    i++;
  }
  h = h % m;
  return h;
}

int hash_search(struct cell *A, char *a) {
  int x = hash_val(a);
  int i = 0;

  while (i <= m) {
    if (A[x].state == 1 && strcmp(A[x].key, a) == 0) {
      return x;
    } else if (A[x].state == 0) {
      return -1;
    } else {
      i++;
      x = (hash_val(a) + i) % m;
    }
  }
  return -1;
}
