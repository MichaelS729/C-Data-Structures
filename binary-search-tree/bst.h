#include "node.h"

typedef struct bst_t {
  int size;
  Node* root;
} BST;

void init_bst(BST* t);

int size(BST* t);

int is_empty(BST* nd);
void empty(BST* t);
void del_bst(BST* t);

int contains_key(BST* t, int key);
int get(BST* t, int key);
void insert(BST* t, int key, int value);
int delete(BST* t, int key);

void print_tree_inorder(BST* t);
