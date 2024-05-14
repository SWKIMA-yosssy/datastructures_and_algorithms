#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

struct node {
  int key;
  struct node *parent;
  struct node *left;
  struct node *right;
};

void inorder_tree_walk(struct node *x);
struct node *tree_search(struct node *T, int a);
struct node *tree_minimum(struct node *x);
struct node *tree_maximum(struct node *x);
struct node *tree_insert(struct node *T, struct node *x);
struct node *tree_delete(struct node *T, struct node *z);

int main(void) {
  struct node *Tree;
  struct node *x, *y, *z;

  int N;
  int Data[maxN];
  int i;
  int a;
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

  Tree = NULL;

  for (i = 0; i < N; i++) {
    x = (struct node *)malloc(sizeof(struct node));
    x->key = Data[i];
    x->parent = x->left = x->right = NULL;
    Tree = tree_insert(Tree, x);
  }
  inorder_tree_walk(Tree);
  printf("\n");
  printf("root: %d max node: %d min node: %d \n", Tree->key,
         tree_maximum(Tree)->key, tree_minimum(Tree)->key);
  printf("\n");
  for (i = 0; i < N; i++) {
    Tree = tree_delete(Tree, tree_search(Tree, Data[i]));
    inorder_tree_walk(Tree);
    printf("\n");
    printf("root: %d max node: %d min node: %d \n\n", Tree->key,
           tree_maximum(Tree)->key, tree_minimum(Tree)->key);
  }
  return 0;
}

struct node *tree_insert(struct node *T, struct node *x) {
  struct node *r, *y, *z;
  int flag = 0; // left = 0, right =1;

  r = T;
  y = NULL;
  z = r;

  while (z != NULL) {
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

  if (y == NULL) {
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

void inorder_tree_walk(struct node *x) {
  if (x != NULL) {
    inorder_tree_walk(x->left);
    printf("%d ", x->key);
    inorder_tree_walk(x->right);
  }
}

struct node *tree_minimum(struct node *x) {
  struct node *y = x;
  while (y->left != NULL) {
    y = y->left;
  }
  return y;
}

struct node *tree_maximum(struct node *x) {
  struct node *y = x;
  while (y->right != NULL) {
    y = y->right;
  }
  return y;
}

struct node *tree_search(struct node *T, int a) {
  struct node *x = T;
  while (x != NULL && x->key != a) {
    if (a < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return x;
}

struct node *tree_delete(struct node *T, struct node *z) {
  struct node *x;
  struct node *y;
  struct node *p;
  struct node *r = T;
  int flag = 0; // number of z's children

  if (z == NULL) { // confirm whether tree is blank or not
    printf("there is no node to delete; tree is blank\n");
    return r;
  } else {
    printf("delete note: %d ", z->key);
  }

  if (z->right != NULL && z->left != NULL) { // z has 2 children
    y = tree_minimum(z->right);
    flag = 2;
  } else {
    y = z;
    flag = 1;
  }
  p = y->parent;
  if (y->right == NULL && y->left == NULL) { // y does not have child
    x = NULL;
    flag = 0;
  } else {
    if (y->right != NULL) {
      x = y->right;
    } else {
      x = y->left;
    }
    x->parent = p;
  }
  if (p == NULL) {
    r = x;
  } else {
    if (flag == 0) {
      if (p->left == z) {
        p->left = NULL;
      } else {
        p->right = NULL;
      }
    } else {
      if (p->left == y) {
        p->left = x;
      } else {
        p->right = x;
      }
    }
  }
  if (y != z) {
    z->key = y->key;
  }
  printf("actual delete node: %d\n", y->key);
  free(y);
  return r;
}
