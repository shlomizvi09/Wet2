#include <iostream>
#include "library2.h"
#include "MusicManager.h"

int main() {
  AVLRankTree<int, int> *new_tree = new AVLRankTree<int, int>();
  int m = 20;
  for (int i = 1; i < m; ++i) {
    new_tree->add(i, i);
  }
  TreeNode<int, int> *tree_node = nullptr;
  std::cout << "the ranks are:\n";
  for (int i = 1; i < m; ++i) {
    std::cout << "key: ";
    tree_node = new_tree->getNodeByRank(i, new_tree->getRoot());
    std::cout << tree_node->getKey() << "\n";
  }
  new_tree->cleanTree(new_tree->getRoot());
  delete new_tree;
  void *music_manager = Init();
  MusicManager *ds = (MusicManager*)music_manager;
  AddArtist(music_manager,111);
  RemoveArtist(music_manager,111);

  return 0;
}
