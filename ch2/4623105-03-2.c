#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

struct cell {
  int key;
  int next;
};

int allocate_object(struct cell *L, int *f);
void free_object(struct cell *L, int *freeL, int *x);
void list_insert(struct cell *L, int *head, int *p, int x);
int list_search(struct cell *L, int *head, int *a);
void list_delete(struct cell *L, int *head, int x);
int list_maximum(struct cell *L, int *head);
int list_minimum(struct cell *L, int *head);

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

  for (i = 0; i < N; i++) {
    List[i].key = Data[i];
    list_insert(List, &head, &head, i);
  }

  for (i = 0; i < N; i++) {
    Data[i] = List[list_minimum(List, &head)].key;
    list_delete(List, &head, list_minimum(List, &head));
  }

  for (i = 0; i < N; i++) {
    printf("%d\n", Data[i]);
  }

  return 0;
}

int allocate_object(struct cell *L, int *f) {
  int x;

  if (*f == -1) {
    printf("error: out of space\n");
    x = -1;
  }

  else {
    x = *f;
    *f = L[*f].next;
  }
  return x;
}

void free_object(struct cell *L, int *freeL, int *x) {
  L[*x].next = *freeL;
  *freeL = *x;
}

void list_insert(struct cell *L, int *head, int *p, int x) {
  if (*p != -1) {
    L[x].next = L[*p].next;
    L[*p].next = x;
  } else {
    L[x].next = *head;
    *head = x;
  }
}

int list_search(struct cell *L, int *head, int *a) {
  int x = *head;
  while (x != -1 && L[x].key != *a) {
    x = L[x].next;
  }
  return x;
}

void list_delete(struct cell *L, int *head, int x) {
  int prev = -1;
  int current = *head;

  // 削除対象のノードを探索
  while (current != -1 && current != x) {
    prev = current;
    current = L[current].next;
  }

  // 削除対象のノードが見つかった場合
  if (current == x) {
    // 直前のノードが存在する場合
    if (prev != -1) {
      L[prev].next = L[x].next;
    } else { // 直前のノードが存在しない場合、削除対象のノードが先頭のノードである
      *head = L[x].next;
    }
  }
}

int list_maximum(struct cell *L, int *head) {
  int x;
  x = *head;
  int y;
  y = x;
  int max = -2147483648;
  while (x != -1) {
    if (L[x].key > max) {
      max = L[x].key;
      y = x;
    }
    x = L[x].next;
  }
  return y;
}

int list_minimum(struct cell *L, int *head) {
  int x;
  x = *head;
  int y;
  y = x;
  int min = 2147483647;
  while (x != -1) {
    if (L[x].key < min) {
      min = L[x].key;
      y = x;
    }
    x = L[x].next;
  }
  return y;
}
