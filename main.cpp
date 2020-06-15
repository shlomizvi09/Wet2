#include <iostream>
#include "AVLRankTree.h"

int main() {
  AVLRankTree<int, int> *new_tree = new AVLRankTree<int, int>();
  for (int i = 0; i < 8; ++i) {
    new_tree->add(i, i);
  }
  new_tree->cleanTree(new_tree->getRoot());
  delete new_tree;
  return 0;
}
