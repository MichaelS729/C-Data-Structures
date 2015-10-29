#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

void init_bst(BST* t) {
  t->size = 0;
  t->root = NULL;
}

int size(BST* t) {
  return t->size;
}

int is_empty(BST* t) {
  return size(t) == 0;
}

void empty_by_node(Node* nd) {
  if (nd == NULL) {
    return;
  }
  empty_by_node(nd->left);
  Node* right = nd->right;
  free(nd);
  empty_by_node(right);
}

void empty(BST* t) {
  empty_by_node(t->root);
}

void del_bst(BST* t) {
  empty(t);
}

int contains_key(BST* t, int key) {
  Node* curr = t->root;
  while ((curr != NULL) || (curr->key != key)) {
    if (key < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return curr != NULL;
}

int get(BST* t, int key) {
  Node* curr = t->root;
  while ((curr != NULL) || (curr->key != key)) {
    if (key < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (curr == NULL) {
    printf("Error: BST does not contain key\n");
    return -1;
  } else {
    return curr->value;
  }
}

void insert(BST* t, int key, int value) {
  if (t->root == NULL) {
    t->root = malloc(sizeof(Node));
    init_node(t->root);
    t->root->key = key;
    t->root->value = value;
  }

  Node* curr = t->root;
  Node* parent = NULL;
  while (curr != NULL) {
    parent = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      curr->value = value;
      return;
    }
  }

  if (key < parent->key) {
    parent->left = malloc(sizeof(Node));
    init_node(parent->left);
    parent->left->key = key;
    parent->left->value = value;
  } else {
    parent->right = malloc(sizeof(Node));
    init_node(parent->right);
    parent->right->key = key;
    parent->right->value = value;
  }

  t->size++;
}

void replace_child(BST* t, Node* parent, Node* old_child, Node* new_child) {
  if (parent == NULL) {
    t->root = new_child;
    return;
  }

  if (parent->left == old_child) {
    parent->left = new_child;
  }
  if (parent->right == old_child) {
    parent->right = new_child;
  }
}

void replace_node(BST* t, Node* nd, Node* nd_parent) {
  if (nd->left == NULL) {
    replace_child(t, nd_parent, nd, nd->right);
    free(nd);
    return;
  }
  if (nd->right == NULL) {
    replace_child(t, nd_parent, nd, nd->left);
    free(nd);
    return;
  }

  Node* curr = nd->right;
  Node* curr_parent = nd;
  while (curr->left != NULL) {
    curr_parent = curr;
    curr = curr->left;
  }

  replace_child(t, curr_parent, curr, curr->right);

  curr->left = nd->left;
  curr->right = nd->right;

  replace_child(t, nd_parent, nd, curr);
  free(nd);
}

int delete(BST* t, int key) {
  Node* curr = t->root;
  Node* parent = NULL;

  while ((curr != NULL) || (curr->key != key)) {
    parent = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (curr == NULL) {
    printf("Error: BST does not contain key\n");
    return -1;
  } else {
    replace_node(t, curr, parent);
  }

  t->size--;
}

void print_by_node(Node* nd) {
  if (nd == NULL) {
    return;
  }
  print_by_node(nd->left);
  printf("Key: %d, Value: %d\n", nd->key, nd->value);
  print_by_node(nd->right);
}

void print_tree_inorder(BST* t) {
  print_by_node(t->root);
  printf("\n");
}

int main(void) {
  return 0;
}
