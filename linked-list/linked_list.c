#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int size(LinkedList* l) {
  return l->size;
};

void init_linked_list(LinkedList* l) {
  l->size = 0;
  l->head = malloc(sizeof(Node));
  l->tail = malloc(sizeof(Node));

  l->head->next = l->tail;
  l->tail->prev = l->head;
}

int get(LinkedList* l, int index) {
  if (is_empty(l)) {
    printf("Error: LinkedList is empty\n");
    return -1;
  }

  Node* curr = l->head->next;
  int i = 0;
  while (i < index) {
    curr = curr->next;
    if (curr == l->tail) {
      printf("Error: Index out of bounds\n");
      return -1;
    }
    i++;
  }
  return curr->value;
}

int get_first(LinkedList* l) {
  return get(l, 0);
}

int get_last(LinkedList* l) {
  if (is_empty(l)) {
    printf("Error: LinkedList is empty\n");
    return -1;
  }
  return l->tail->prev->value;
}

void add(LinkedList* l, int index, int val) {
  Node* behind = l->head;
  int i = 0;
  while (i < index) {
    behind = behind->next;
    if (behind == l->tail) {
      printf("Error: Index out of bounds\n");
      return;
    }
    i++;
  }

  Node* node = malloc(sizeof(Node));
  node->value = val;
  node->prev = behind;
  node->next = behind->next;
  behind->next->prev = node;
  behind->next = node;

  l->size++;
}

void add_front(LinkedList* l, int val) {
  add(l, 0, val);
}

void add_last(LinkedList* l, int val) {
  Node* node = malloc(sizeof(Node));
  node->value = val;
  node->prev = l->tail->prev;
  node->next = l->tail;
  l->tail->prev->next = node;
  l->tail->prev = node;

  l->size++;
}

int delete(LinkedList* l, int index) {
  if (is_empty(l)) {
    printf("Error: LinkedList is empty\n");
    return -1;
  }

  Node* curr = l->head->next;
  int i = 0;
  while (i < index) {
    curr = curr->next;
    if (curr == l->tail) {
      printf("Error: Index out of bounds\n");
      return -1;
    }
    i++;
  }

  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  int val = curr->value;
  free(curr);

  l->size--;
  return val;
}

int delete_first(LinkedList* l) {
  return delete(l, 0);
}

int delete_last(LinkedList* l) {
  if (is_empty(l)) {
    printf("Error: LinkedList is empty\n");
    return -1;
  }

  Node* removed = l->tail->prev;
  removed->prev->next = removed->next;
  removed->next->prev = removed->prev;
  int val = removed->value;
  free(removed);

  l->size--;
  return val;
}

int is_empty(LinkedList* l) {
  return size(l) == 0;
}

void empty(LinkedList* l) {
  while (size(l) > 0) {
    delete_first(l);
  }
}

void del_linked_list(LinkedList* l) {
  empty(l);
  free(l->head);
  free(l->tail);
}

void print_list(LinkedList* l) {
  Node* curr = l->head->next;
  while (curr != l->tail) {
    printf("%d ", curr->value);
    curr = curr->next;
  }
  printf("\n");
}

int main(void) {
  LinkedList* l = malloc(sizeof(LinkedList));
  init_linked_list(l);
  printf("Initial size should be 0: %d\n", size(l));
  printf("\n");

  printf("Should output error messsages:\n");
  get_first(l);
  get_last(l);
  delete_first(l);
  delete_last(l);
  printf("\n");

  printf("Should be [5 3 7 6]:\n");
  add_front(l, 3);
  add_front(l, 5);
  add(l, 2, 6); // Add value 6 to index 2 (3rd element)
  add(l, 2, 7); // Add value 7 to index 2 (3rd element)
  print_list(l);
  printf("Size should be 4: %d\n", size(l));
  printf("\n");

  printf("Should result in out-of-bounds errors:\n");
  get(l, 3);
  add(l, 5, 9); // Attempt to add value 9 to index 5, without an index 4
  delete(l, 5); // Attempt to remove index 5, without an index 4
  printf("\n");

  printf("Removing index 2, should output 7:\n");
  printf("%d\n", delete(l, 2));
  printf("Should be [5 3 6]\n");
  print_list(l);
  printf("Size should be 3: %d\n", size(l));
  printf("\n");

  empty(l);
  printf("List should be empty:\n");
  print_list(l);
  printf("Size should be 0: %d\n", size(l));
  printf("\n");

  printf("Should be [1 2 3]:\n");
  add_last(l, 1);
  add_last(l, 2);
  add_last(l, 3);
  print_list(l);
  printf("Size should be 3: %d\n", size(l));
  printf("\n");

  printf("Should be [1 2]:\n");
  delete_last(l);
  print_list(l);
  printf("Size should be 2: %d\n", size(l));
  printf("\n");

  printf("Should be [1 2]: [%d %d]\n", get(l, 0), get(l, 1));
  printf("Should be [1 2]: [%d %d]\n", get_first(l), get_last(l));
  printf("\n");

  delete_last(l);
  printf("Should be [1]\n");
  print_list(l);
  printf("Should be [1]: [%d]\n", get_first(l));
  printf("Should be [1]: [%d]\n", get_last(l));
  printf("Size should be 1: %d\n", size(l));

  del_linked_list(l);
  printf("Size should b 0: %d\n", size(l));
  free(l);
  return 0;
}
