#include <stdlib.h>
#include "node.h"

void init_node(Node* nd) {
  if (nd != NULL) {
    nd->left = NULL;
    nd->right = NULL;
  }
}
