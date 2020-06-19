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
    HashTableResult tmp_result = HASH_FAILURE;
    tmp_result = table->search(artistID, &tmp_node);
    if (tmp_result == HASH_DONT_EXIST)
        return MM_NOT_EXISTS;
    if (tmp_node->getData()->getData().getSize() != 0)
        return MM_FAIL;
    delete tmp_node->getData();
    tmp_result = table->remove(artistID);
    if (tmp_result == HASH_SUCCESS)
        return MM_SUCCESS;
    return MM_FAIL;
}

