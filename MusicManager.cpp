//
// Created by Arik on 19/06/2020.
//

#include "MusicManager.h"

MusicManagerResult MusicManager::AddArtist(int artistID) {
    HashTableResult tmp_result = HASH_FAILURE;
    FirstTreeNodeData *new_data = new FirstTreeNodeData();
    tmp_result = table->insert(artistID,new_data);
    if(tmp_result==HASH_ALREADY_EXIST){
        delete new_data;
        return MM_EXISTS;
    }
    if(tmp_result==HASH_SUCCESS)
        return MM_SUCCESS;
    return MM_FAIL;
}

