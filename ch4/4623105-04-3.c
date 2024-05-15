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
struct rbnode *right_rotate(struct rbnode *T, struct rbnode *x);
int bh(struct rbnode *x);

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
  printf("root: %d max rbnode: %d min rbnode: %d black height: %d\n", Tree->key,
         tree_maximum(Tree)->key, tree_minimum(Tree)->key, bh(Tree));
  printf("\n");
  return 0;
}

struct rbnode *rb_insert(struct rbnode *T, struct rbnode *x) {
  struct rbnode *y = NILT;
  struct rbnode *z = T;

  // 正しい位置を見つけるためのループ
  while (z != NILT) {
    y = z;
    if (x->key < z->key)
      z = z->left;
    else
      z = z->right;
  }

  // 親ノードの設定
  x->parent = y;
  if (y == NILT) {
    T = x;
  } else if (x->key < y->key) {
    y->left = x;
  } else {
    y->right = x;
  }

  x->left = NILT;
  x->right = NILT;
  x->color = 0; // 新しいノードは赤色

  // 修正ロジック
  struct rbnode *uncle;
  while (x != T && x->parent->color == 0) {
    if (x->parent == x->parent->parent->left) {
      uncle = x->parent->parent->right;
      if (uncle->color == 0) {
        x->parent->color = 1;
        uncle->color = 1;
        x->parent->parent->color = 0;
        x = x->parent->parent;
      } else {
        if (x == x->parent->right) {
          x = x->parent;
          T = left_rotate(T, x);
        }
        x->parent->color = 1;
        x->parent->parent->color = 0;
        T = right_rotate(T, x->parent->parent);
      }
    } else {
      uncle = x->parent->parent->left;
      if (uncle->color == 0) {
        x->parent->color = 1;
        uncle->color = 1;
        x->parent->parent->color = 0;
        x = x->parent->parent;
      } else {
        if (x == x->parent->left) {
          x = x->parent;
          T = right_rotate(T, x);
        }
        x->parent->color = 1;
        x->parent->parent->color = 0;
        T = left_rotate(T, x->parent->parent);
      }
    }
  }
  T->color = 1;
  return T;
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

struct rbnode *right_rotate(struct rbnode *T, struct rbnode *x) {
  struct rbnode *r, *y, *z, *p;

  r = T;
  y = x->left;
  z = y->right;

  x->left = z;
  z->parent = x;

  p = x->parent;
  if (p == NILT) {
    r = y;
  } else {
    if (x == p->right) {
      p->right = y;
    } else {
      p->left = y;
    }
  }
  y->right = x;
  x->parent = y;
  y->parent = p;
  return r;
}

int bh(struct rbnode *x) {
  int h, h_2;
  if (x == NILT) {
    return 0;
  } else {
    h = bh(x->left) + x->left->color;
    h_2 = bh(x->right) + x->right->color;
  }

  if (h != h_2) {
    fprintf(stderr, "invalid black height\n");
    return -1;
  } else {
    return h;
  }
}
