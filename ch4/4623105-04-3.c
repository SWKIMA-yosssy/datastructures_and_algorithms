#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

struct rbnode {
  int key;
  struct rbnode *parent;
  struct rbnode *left;
  struct rbnode *right;
  unsigned int color : 1;
};

void inorder_tree_walk(struct rbnode *x);
struct rbnode *tree_search(struct rbnode *T, int a);
struct rbnode *tree_minimum(struct rbnode *x);
struct rbnode *tree_maximum(struct rbnode *x);
struct rbnode *rb_insert(struct rbnode *T, struct rbnode *x);
struct rbnode *left_rotate(struct rbnode *T, struct rbnode *x);

struct rbnode *NILT;
int main(void) {
  struct rbnode *Tree;
  struct rbnode *x, *y, *z;

  int N;
  int Data[maxN];
  int i;
  int a;
  char fname[128];
  FILE *fp;

  NILT = (struct rbnode *)malloc(sizeof(struct rbnode));
  NILT->color = 1;
  Tree = NILT;

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

  Tree = NILT;

  for (i = 0; i < N; i++) {
    x = (struct rbnode *)malloc(sizeof(struct rbnode));
    x->key = Data[i];
    x->parent = x->left = x->right = NILT;
    Tree = rb_insert(Tree, x);
  }
  inorder_tree_walk(Tree);
  printf("\n");
  printf("root: %d max rbnode: %d min rbnode: %d \n", Tree->key,
         tree_maximum(Tree)->key, tree_minimum(Tree)->key);
  printf("\n");
  return 0;
}

struct rbnode *rb_insert(struct rbnode *T, struct rbnode *x) {
  struct rbnode *r, *y, *z;
  int flag = 0; // left = 0, right =1;

  r = T;
  y = NILT;
  z = r;

  while (z != NILT) {
    if (x->key < z->key) {
      y = z;
      z = z->left;
      flag = 0;
    } else {
      y = z;
      z = z->right;
      flag = 1;
    }
  }
  x->parent = y;

  if (y == NILT) {
    r = x;
  } else {
    if (flag) {
      y->right = x;
    } else {
      y->left = x;
    }
  }

  return r;
}

void inorder_tree_walk(struct rbnode *x) {
  if (x != NILT) {
    inorder_tree_walk(x->left);
    printf("%d ", x->key);
    inorder_tree_walk(x->right);
  }
}

struct rbnode *tree_minimum(struct rbnode *x) {
  struct rbnode *y = x;
  while (y->left != NILT) {
    y = y->left;
  }
  return y;
}

struct rbnode *tree_maximum(struct rbnode *x) {
  struct rbnode *y = x;
  while (y->right != NILT) {
    y = y->right;
  }
  return y;
}

struct rbnode *tree_search(struct rbnode *T, int a) {
  struct rbnode *x = T;
  while (x != NILT && x->key != a) {
    if (a < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return x;
}

struct rbnode *left_rotate(struct rbnode *T, struct rbnode *x) {
  struct rbnode *r, *y, *z, *p;

  r = T;
  y = x->right;
  z = y->left;

  x->right = z;
  z->parent = x;

  p = x->parent;
  if (p == NILT) {
    r = y;
  } else {
    if (x == p->left) {
      p->left = y;
    } else {
      p->right = y;
    }
  }
  y->left = x;
  x->parent = y;
  y->parent = p;
  return r;
}

struct rbnode *left_rotate(struct rbnode *T, struct rbnode *x) {
  struct rbnode *r, *y, *z, *p;

  r = T;
  y = x->right;
  z = y->left;

  x->right = z;
  z->parent = x;

  p = x->parent;
  if (p == NILT) {
    r = y;
  } else {
    if (x == p->left) {
      p->left = y;
    } else {
      p->right = y;
    }
  }
  y->left = x;
  x->parent = y;
  y->parent = p;
  return r;
}
