#include <iostream>
#include "AVLRankTree.h"

int main() {
  AVLRankTree<int, int> *new_tree = new AVLRankTree<int, int>();
  for (int i = 1; i < 8957; ++i) {
    new_tree->add(i, i);
  }
  int rank = new_tree->getRank(1504);
  new_tree->cleanTree(new_tree->getRoot());
  delete new_tree;
  return 0;
}
