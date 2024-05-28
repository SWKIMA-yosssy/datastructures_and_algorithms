#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 20
#define m 97
#define maxN 50

struct cell {
  char key[W + 1];
  int next;
};

int allocate_object(struct cell *L, int *f);
void free_object(struct cell *L, int *freeL, int *x);
int chained_hash_search(int *A, struct cell *L, char *a);
void chained_hash_insert(int *A, struct cell *L, int x);
void chained_hash_delete(int *A, struct cell *L, int x);
int list_length(struct cell *L, int a);

int main(void) {
  struct cell List[maxN];
  int A[m];
  int N;
  int freeL;
  int head;
  int i, h;
  int y;
  int x;
  char word[W + 1];
  char fname[128];
  FILE *fp;

  for (i = 0; i < maxN - 1; i++) {
    List[i].next = i + 1;
  }
  List[maxN - 1].next = -1;
  freeL = 0;
  for (h = 0; h < m; h++) {
    A[h] = -1;
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
    y = chained_hash_search(A, List, word);
    if (y == -1) {
      x = allocate_object(List, &freeL);
      strcpy(List[x].key, word);
      chained_hash_insert(A, List, x);
    }
  }
  fclose(fp);
  for (h = 0; h < m; h++) { // show length of A[h]
    if (list_length(List, A[h]) != 0) {
      printf("A[%d] : length = %d\n", h, list_length(List, A[h]));
    }
  }

  printf("###finish insert###\n");
  fp = fopen(fname, "r");
  fscanf(fp, "%d", &N);
  if (N > maxN) {
    N = maxN;
  }

  for (i = 0; i < N; i++) {
    fscanf(fp, "%s", word); // delete list node
    x = chained_hash_search(A, List, word);
    if (x != -1) {
      chained_hash_delete(A, List, x);
      free_object(List, &freeL, &x);
    }
  }
  fclose(fp);
  for (h = 0; h < m; h++) { // show length of A[m];
    if (list_length(List, A[h]) != 0) {
      printf("A[%d] : length = %d\n", h, list_length(List, A[h]));
    }
  }
  printf("###finish list delete\n");
  return 0;
}

int allocate_object(struct cell *L, int *f) {
  int x;

  if (*f == -1) {
    printf("error: out of space\n");
    x = -1;
  } else {
    x = *f;
    *f = L[*f].next;
  }
  return x;
}

void free_object(struct cell *L, int *freeL, int *x) {
  L[*x].next = *freeL;
  *freeL = *x;
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

void chained_hash_insert(int *A, struct cell *L, int x) {
  L[x].next = A[hash_val(L[x].key)];
  A[hash_val(L[x].key)] = x;
}

int chained_hash_search(int *A, struct cell *L, char *a) {
  int x;
  x = A[hash_val(a)];
  while (x != -1 && strcmp(L[x].key, a) != 0) {
    x = L[x].next;
  }
  return x;
}

int list_length(struct cell *L, int a) {
  int counter = 0;
  int x = a;
  while (x != -1) {
    x = L[x].next;
    counter++;
  }
  return counter;
}
void chained_hash_delete(int *A, struct cell *L, int x) {
  int h = hash_val(L[x].key);
  int z = A[h];

  if (z == x) {
    z = -1;
  } else {
    while (z != -1 && L[z].next != x) {
      z = L[z].next;
    }
  }

  if (z != -1) {
    L[z].next = L[x].next;
  } else {
    A[h] = L[x].next;
  }
}
