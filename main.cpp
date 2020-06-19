#include <iostream>
#include "library2.h"
#include "MusicManager.h"

int main() {
  AVLRankTree<int, int> *new_tree = new AVLRankTree<int, int>();
  int nums[] = {1, 2, 3, -4, -5, 0, -100, 200, -400};
  for (int i = 0; i < sizeof(nums) / sizeof(nums[i]); ++i) {
    new_tree->add(nums[i], nums[i]);
  }
  for (int i = sizeof(nums) / sizeof(nums[i]) - 1; i >= 0; --i) {
    new_tree->remove(nums[i]);
  }
  new_tree->cleanTree(new_tree->getRoot());
  delete new_tree;

  return 0;
}
