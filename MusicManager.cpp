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

MusicManagerResult MusicManager::RemoveArtist(int artistID) {
    TreeNode<int, FirstTreeNodeData *> *tmp_node = nullptr;
    HashTableResult tmp_result = table->search(artistID, &tmp_node);
    if (tmp_result == HASH_DONT_EXIST)
        return MM_NOT_EXISTS;
    if (!(tmp_node->getData()->getAuxTree()->isEmpty()))
        return MM_FAIL;
    delete tmp_node->getData();
    tmp_result = table->remove(artistID);
    if (tmp_result == HASH_SUCCESS)
        return MM_SUCCESS;
    return MM_FAIL;
}

MusicManagerResult MusicManager::AddSong(int artistID, int songID) {
    TreeNode<int, FirstTreeNodeData *> *tmp_node = nullptr;
    HashTableResult tmp_result = table->search(artistID, &tmp_node);
    if (tmp_result == HASH_DONT_EXIST)
        return MM_NOT_EXISTS;
    TreeNode<int, SecondTreeNodeData *> *tmp_node2 = nullptr;
    AVLRankTreeResult tmp_tree_res = tmp_node->getData()->getAuxTree()->searchNode(songID, &tmp_node2);
    if (tmp_tree_res == AVL_KeyAlreadyExists)
        return MM_FAIL;
    SecondTreeNodeData *tmp_data = new SecondTreeNodeData(0,songID);
    SecondTreeNodeData *tmp_data_aux = new SecondTreeNodeData(0,songID);
    ThirdTreeNodeData *third_tree_data = new ThirdTreeNodeData(0,artistID,songID);
    tmp_node->getData()->getAuxTree()->add(songID,tmp_data_aux);
    tmp_node->getData()->getTree()->add(*tmp_data,tmp_data);
    deg_tree->add(*third_tree_data,third_tree_data);
    return MM_SUCCESS;
}

