#include <iostream>
#include "library2.h"
#include "MusicManager.h"

int main() {
    /* AVLRankTree<int, int> *new_tree = new AVLRankTree<int, int>();
     int nums[] = {1, 5, 6, 7, 9, 13, 15, 22, 23, 40};
     for (int i = 0; i < 10; ++i) {
       new_tree->add(nums[i], nums[i]);
     }
     TreeNode<int, int> *tree_node = nullptr;
     int i = 0;
     int m = 1000 * sizeof(nums) / sizeof(nums[0]);
     while (m > 0) {
       std::cin >> i;
       tree_node = new_tree->getNodeByRank(i, new_tree->getRoot());
       if (tree_node == nullptr) {
         std::cout << "error. no such rank.\n";
         continue;
       }
       std::cout << "key: " << tree_node->getKey();
       std::cout << " ,rank: " << i << "\n";
       m--;
     }
     new_tree->cleanTree(new_tree->getRoot());
     delete new_tree;*/
    void *music_manager = Init();
    MusicManager *ds = (MusicManager *) music_manager;
    AddArtist(music_manager, 111);
    RemoveArtist(music_manager, 111);
    RemoveArtist(music_manager, 11);
    AddArtist(music_manager, 111);
    AddSong(music_manager, 111, 22);
    AddSong(music_manager, 111, 2);
    AddSong(music_manager, 111, 3);
    AddSong(music_manager, 111, 5);
    AddSong(music_manager, 111, 45);
    AddSong(music_manager, 111, 33);
    AddSong(music_manager, 111, 9);

    RemoveSong(music_manager, 111, 5);
    RemoveSong(music_manager, 111, 45);
    RemoveSong(music_manager, 111, 33);
    RemoveSong(music_manager, 111, 9);
    Quit(&music_manager);



    return 0;
}
