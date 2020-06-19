//
// Created by Arik on 19/06/2020.
//

#include "MusicManager.h"

MusicManagerResult MusicManager::AddArtist(int artistID) {
  HashTableResult tmp_result = HASH_FAILURE;
  FirstTreeNodeData *new_data = new FirstTreeNodeData();
  tmp_result = table->insert(artistID, new_data);
  if (tmp_result == HASH_ALREADY_EXIST) {
    delete new_data;
    return MM_EXISTS;
  }
  if (tmp_result == HASH_SUCCESS)
    return MM_SUCCESS;
  return MM_FAIL;
}

MusicManagerResult MusicManager::AddToSongCount(int artistID, int songID, int count) {
  if (artistID <= 0 || songID <= 0 || count <= 0) {
    return MM_INVALID_INPUT;
  }
  TreeNode<int, FirstTreeNodeData *> *artist_node = nullptr;
  if (this->table->search(artistID, &artist_node) == HASH_DONT_EXIST) {
    return MM_FAIL;
  }
  TreeNode<int, SecondTreeNodeData *> *aux_song_node = nullptr;
  if (artist_node->getData()->getAuxTree()->searchNode(songID, &aux_song_node) == AVL_KeyNotFound) {
    return MM_NOT_EXISTS;
  }
  int old_num_of_plays = aux_song_node->getData()->getPlays();
  TreeNode<SecondTreeNodeData, SecondTreeNodeData *> *second_tree_song_node = nullptr;
  AVLRankTree<SecondTreeNodeData, SecondTreeNodeData *>
      *artist_first_tree = artist_node->getData()->getTree();
  if (artist_first_tree->searchNode(*(aux_song_node->getData()), &second_tree_song_node)
      == AVL_KeyNotFound) {
    return MM_NOT_EXISTS;
  }
  ThirdTreeNodeData
      temp_third_tree_song_data = ThirdTreeNodeData(old_num_of_plays, artistID, songID);
  TreeNode<ThirdTreeNodeData, ThirdTreeNodeData *> *third_tree_song_node = nullptr;
  if (this->deg_tree->searchNode(temp_third_tree_song_data, &third_tree_song_node)
      == AVL_KeyNotFound) {
    return MM_NOT_EXISTS;
  }
  SecondTreeNodeData *second_tree_song_data = second_tree_song_node->getData();
  artist_first_tree->remove(*second_tree_song_data);
  second_tree_song_data->addToPlays(count);
  aux_song_node->getData()->addToPlays(count);
  artist_first_tree->add(*second_tree_song_data, second_tree_song_data);

  ThirdTreeNodeData *third_tree_song_data = third_tree_song_node->getData();
  this->deg_tree->remove(*third_tree_song_data);
  third_tree_song_data->addToPlays(count);
  this->deg_tree->add(*third_tree_song_data, third_tree_song_data);

  return MM_SUCCESS;
}
