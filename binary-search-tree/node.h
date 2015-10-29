typedef struct node_t {
  int key;
  int value;
  struct node_t* left;
  struct node_t* right;
} Node;

void init_node(Node* nd);
