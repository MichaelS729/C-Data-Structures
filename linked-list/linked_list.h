#include "node.h"

typedef struct linked_list_t {
  int size;
  Node* head;
  Node* tail;
} LinkedList;

int size(LinkedList* l);
void init_linked_list(LinkedList* l);

int get(LinkedList* l, int index);
int getFirst(LinkedList* l);
int getLast(LinkedList* l);

void add(LinkedList* l, int index, int val);
void add_front(LinkedList* l, int val);
void add_last(LinkedList* l, int val);

int delete(LinkedList* l, int index);
int delete_first(LinkedList* l);
int delete_last(LinkedList* l);

int is_empty(LinkedList* l);
void empty(LinkedList* l);
void del_linked_list(LinkedList* l);
