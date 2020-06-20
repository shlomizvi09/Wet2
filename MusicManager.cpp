//
// Created by Arik on 19/06/2020.
//

#include "MusicManager.h"

MusicManagerResult MusicManager::AddArtist(int artistID) {
    HashTableResult tmp_result = HASH_FAILURE;
    FirstTreeNodeData *new_data = new FirstTreeNodeData();
    tmp_result = hash_table->insert(artistID, new_data);
    if (tmp_result == HASH_ALREADY_EXIST) {
        delete new_data;
        return MM_EXISTS;
    }
    if (tmp_result == HASH_SUCCESS)
        return MM_SUCCESS;
    return MM_FAIL;
}

MusicManagerResult MusicManager::RemoveArtist(int artistID) {
    TreeNode < int, FirstTreeNodeData * > *tmp_node = nullptr;
    HashTableResult tmp_result = hash_table->search(artistID, &tmp_node);
    if (tmp_result == HASH_DONT_EXIST)
        return MM_NOT_EXISTS;
    if (!(tmp_node->getData()->getAuxTree()->isEmpty()))
        return MM_FAIL;
    delete tmp_node->getData();
    tmp_result = hash_table->remove(artistID);
    if (tmp_result == HASH_SUCCESS)
        return MM_SUCCESS;
    return MM_FAIL;
}

MusicManagerResult MusicManager::AddSong(int artistID, int songID) {
    TreeNode<int, FirstTreeNodeData *> *tmp_node = nullptr;
    HashTableResult tmp_result = hash_table->search(artistID, &tmp_node);
    if (tmp_result == HASH_DONT_EXIST)
        return MM_NOT_EXISTS;
    TreeNode<int, SecondTreeNodeData *> *tmp_node2 = nullptr;
    AVLRankTreeResult
            tmp_tree_res = tmp_node->getData()->getAuxTree()->searchNode(songID, &tmp_node2);
    if (tmp_tree_res == AVL_KeyAlreadyExists)
        return MM_FAIL;
    SecondTreeNodeData *tmp_data = new SecondTreeNodeData(0, songID);
    SecondTreeNodeData *tmp_data_aux = new SecondTreeNodeData(0, songID);
    ThirdTreeNodeData *third_tree_data = new ThirdTreeNodeData(0, artistID, songID);
    if (tmp_node->getData()->getAuxTree()->add(songID, tmp_data_aux) != AVL_SUCCESS) {
        delete tmp_data;
        delete tmp_data_aux;
        delete third_tree_data;
        return MM_FAIL;
    }
    if (tmp_node->getData()->getTree()->add(*tmp_data, tmp_data) != AVL_SUCCESS) {
        tmp_node->getData()->getAuxTree()->remove(songID);
        delete tmp_data;
        delete tmp_data_aux;
        delete third_tree_data;
        return MM_FAIL;
    }
    if (rank_songs_tree->add(*third_tree_data, third_tree_data) != AVL_SUCCESS) {
        tmp_node->getData()->getAuxTree()->remove(songID);
        tmp_node->getData()->getTree()->remove(*tmp_data);
        delete tmp_data;
        delete tmp_data_aux;
        delete third_tree_data;
        return MM_FAIL;
    }
    return MM_SUCCESS;

}

MusicManagerResult MusicManager::RemoveSong(int artistID, int songID) {
    TreeNode < int, FirstTreeNodeData * > *tmp_node = nullptr;
    int tmp_plays = -1;
    HashTableResult tmp_result = hash_table->search(artistID, &tmp_node);
    if (tmp_result == HASH_DONT_EXIST)
        return MM_NOT_EXISTS;
    TreeNode < int, SecondTreeNodeData * > *tmp_node2 = nullptr;
    AVLRankTreeResult
            tmp_tree_res = tmp_node->getData()->getAuxTree()->searchNode(songID, &tmp_node2);
    if (tmp_tree_res == AVL_KeyNotFound)
        return MM_FAIL;
    TreeNode < int, SecondTreeNodeData * > *node1 = nullptr;
    TreeNode < SecondTreeNodeData, SecondTreeNodeData * > *node2 = nullptr;
    TreeNode < ThirdTreeNodeData, ThirdTreeNodeData * > *node3 = nullptr;
    tmp_node->getData()->getAuxTree()->searchNode(songID, &node1);
    tmp_plays = node1->getData()->getPlays();
    SecondTreeNodeData tmp_data2(tmp_plays, songID);
    tmp_node->getData()->getTree()->searchNode(tmp_data2, &node2);
    delete node2->getData();
    tmp_node->getData()->getTree()->remove(tmp_data2);
    delete node1->getData();
    tmp_node->getData()->getAuxTree()->remove(songID);
    ThirdTreeNodeData tmp_data3(tmp_plays, artistID, songID);
    rank_songs_tree->searchNode(tmp_data3, &node3);
    delete node3->getData();
    rank_songs_tree->remove(tmp_data3);
    return MM_SUCCESS;
}

MusicManagerResult MusicManager::AddToSongCount(int artistID, int songID, int count) {
    if (artistID <= 0 || songID <= 0 || count <= 0) {
        return MM_INVALID_INPUT;
    }
    TreeNode < int, FirstTreeNodeData * > *artist_node = nullptr;
    if (this->hash_table->search(artistID, &artist_node) == HASH_DONT_EXIST) {
        return MM_FAIL;
    }
    TreeNode < int, SecondTreeNodeData * > *aux_song_node = nullptr;
    if (artist_node->getData()->getAuxTree()->searchNode(songID, &aux_song_node) == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    int old_num_of_plays = aux_song_node->getData()->getPlays();
    TreeNode < SecondTreeNodeData, SecondTreeNodeData * > *second_tree_song_node = nullptr;
    AVLRankTree < SecondTreeNodeData, SecondTreeNodeData * >
                                      *artist_first_tree = artist_node->getData()->getTree();
    if (artist_first_tree->searchNode(*(aux_song_node->getData()), &second_tree_song_node)
        == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    ThirdTreeNodeData
            temp_third_tree_song_data = ThirdTreeNodeData(old_num_of_plays, artistID, songID);
    TreeNode < ThirdTreeNodeData, ThirdTreeNodeData * > *third_tree_song_node = nullptr;
    if (this->rank_songs_tree->searchNode(temp_third_tree_song_data, &third_tree_song_node)
        == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    SecondTreeNodeData *second_tree_song_data = second_tree_song_node->getData();
    artist_first_tree->remove(*second_tree_song_data);
    second_tree_song_data->addToPlays(count);
    aux_song_node->getData()->addToPlays(count);
    artist_first_tree->add(*second_tree_song_data, second_tree_song_data);

    ThirdTreeNodeData *third_tree_song_data = third_tree_song_node->getData();
    this->rank_songs_tree->remove(*third_tree_song_data);
    third_tree_song_data->addToPlays(count);
    this->rank_songs_tree->add(*third_tree_song_data, third_tree_song_data);
    return MM_SUCCESS;
}

MusicManagerResult MusicManager::GetArtistBestSong(int artistID, int *songId) {
    if (artistID <= 0 || songId == nullptr) {
        return MM_INVALID_INPUT;
    }
    TreeNode < int, FirstTreeNodeData * > *artist_first_tree_node = nullptr;
    if (this->hash_table->search(artistID, &artist_first_tree_node) == HASH_DONT_EXIST) {
        return MM_NOT_EXISTS;
    }
    FirstTreeNodeData *artist_first_tree_data = artist_first_tree_node->getData();
    if (artist_first_tree_data->getTree()->isEmpty()) {
        return MM_FAIL;
    }
    *songId = artist_first_tree_data->getTree()->getSmallest()->getData()->getSongID();
    return MM_SUCCESS;
}

MusicManagerResult MusicManager::GetRecommendedSongInPlace(int rank, int *artistId, int *songId) {
    if (rank <= 0 || artistId == nullptr || songId == nullptr) {
        return MM_INVALID_INPUT;
    }
    if (rank > this->rank_songs_tree->getSize()) {
        return MM_FAIL;
    }
    TreeNode < ThirdTreeNodeData, ThirdTreeNodeData * > *recommended_song_node = nullptr;
    recommended_song_node =
            this->rank_songs_tree->getNodeByRank(rank, this->rank_songs_tree->getRoot());
    if (recommended_song_node == nullptr) {
        return MM_FAIL;
    }
    *artistId = recommended_song_node->getKey().getSingerID();
    *songId = recommended_song_node->getKey().getSongID();
    return MM_SUCCESS;
}

void MusicManager::DeleteMM() {
    DeleteDegTreeData(rank_songs_tree->getRoot());
    rank_songs_tree->cleanTree(rank_songs_tree->getRoot());
    for (int i = 0; i < hash_table->getArraySize(); ++i) {
        PatrolSingersTree(hash_table->getArray()[i]->getRoot());
    }
}

void MusicManager::DeleteDegTreeData(TreeNode<ThirdTreeNodeData, ThirdTreeNodeData *> *root) {
    if (root == nullptr)
        return;
    DeleteDegTreeData(root->getLeftSon());
    DeleteDegTreeData(root->getRightSon());
    delete root->getData();
}

void MusicManager::DeleteSingerTreeData(TreeNode<SecondTreeNodeData, SecondTreeNodeData *> *root) {
    if (root == nullptr)
        return;
    DeleteSingerTreeData(root->getLeftSon());
    DeleteSingerTreeData(root->getRightSon());
    delete root->getData();
}

void MusicManager::DeleteSingerAuxTreeData(TreeNode<int, SecondTreeNodeData *> *root) {
    if (root == nullptr)
        return;
    DeleteSingerAuxTreeData(root->getLeftSon());
    DeleteSingerAuxTreeData(root->getRightSon());
    delete root->getData();
}

void MusicManager::PatrolSingersTree(TreeNode<int, FirstTreeNodeData *> *root) {
    if (root == nullptr)
        return;
    PatrolSingersTree(root->getRightSon());
    PatrolSingersTree(root->getLeftSon());
    DeleteSingerTreeData(root->getData()->getTree()->getRoot());
    root->getData()->getTree()->cleanTree(root->getData()->getTree()->getRoot());
    DeleteSingerAuxTreeData(root->getData()->getAuxTree()->getRoot());
    root->getData()->getAuxTree()->cleanTree(root->getData()->getAuxTree()->getRoot());
}