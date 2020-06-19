//
// Created by Arik on 10/06/2020.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "AVLRankTree.h"

typedef enum HashTableResult {
    HASH_SUCCESS,
    HASH_FAILURE,
    HASH_ALREADY_EXIST,
    HASH_DONT_EXIST,
} HashTableResult;

template<class Key, class Data>
class HashTable {
    int array_size;
    int size;
    AVLRankTree<Key, Data> **trees;
public:
    HashTable() : array_size(11), size(0) {
        trees = new AVLRankTree<Key, Data> *[array_size];
        for (int i = 0; i < array_size; ++i) {
            trees[i] = new AVLRankTree<Key, Data>();
        }
    }

    ~HashTable() {
        for (int i = 0; i < array_size; ++i) {
            DeleteTreeData(trees[i]->getRoot());
            trees[i]->cleanTree(trees[i]->getRoot());
            delete trees[i];
        }
        delete [] trees;
    }

    int HashFunc(int x, int size) {
        return x % size;
    }

    void DeleteTreeData(TreeNode<Key, Data> *root) {
        if (root == nullptr)
            return;
        DeleteTreeData(root->getRightSon());
        DeleteTreeData(root->getLeftSon());
        delete root->getData();
    }


    HashTableResult search(int x,TreeNode<Key,Data> **node) {
        int tmp_cell = HashFunc(x, array_size);
        AVLRankTree<Key, Data> *tmp_tree = trees[tmp_cell];
        AVLRankTreeResult tmp_result = AVL_KeyNotFound;
        tmp_result=trees[tmp_cell]->searchNode(x,&node);
        if(tmp_result==AVL_SUCCESS)
            return HASH_ALREADY_EXIST;
        return HASH_DONT_EXIST;
    }

    HashTableResult insert(int x, Data data) {
        HashTableResult tmp_result = HASH_FAILURE;
        TreeNode<Key,Data> **tmp_node = nullptr;
        tmp_result=search(x,tmp_node);
        if(tmp_result==HASH_ALREADY_EXIST)
            return HASH_ALREADY_EXIST;
        int tmp_cell = HashFunc(x, array_size);
        trees[tmp_cell]->add(x,data);
        size++;
        if(size>=array_size)
            rehash(array_size*2);
        return HASH_SUCCESS;
    }

    HashTableResult remove(int x){
        HashTableResult tmp_result = HASH_FAILURE;
        TreeNode<Key,Data> *node= nullptr;
        tmp_result=search(x,node);
        if(tmp_result==HASH_DONT_EXIST)
            return HASH_DONT_EXIST;
        int tmp_cell = HashFunc(x, array_size);
        trees[tmp_cell]->remove(x);
        size--;
        if(size<array_size/4 && array_size>11)
            rehash(array_size/2);
        return HASH_SUCCESS;
    }

    HashTableResult rehash(int new_size){
        AVLRankTree<Key,Data>** new_tree=new AVLRankTree<Key,Data>*[new_size];
        for (int i = 0; i < new_size; ++i) {
            new_tree[i] = new AVLRankTree<Key, Data>();
        }
        for (int i = 0; i <array_size ; ++i) {
            CopyTree(trees[i]->getRoot(),new_tree,new_size);
            trees[i]->cleanTree(trees[i]->getRoot());
            delete trees[i];
        }
        delete [] this->trees;
        this->trees=new_tree;
        this->array_size=new_size;
        return HASH_SUCCESS;

    }

    void printTable(){
        for (int i = 0; i <array_size ; ++i) {
            trees[i]->print(In);
        }
    }

    void CopyTree(TreeNode<Key, Data> *root, AVLRankTree<Key, Data> **new_table, int new_size){
        if(root== nullptr)
            return;
        CopyTree(root->getLeftSon(), new_table, new_size);
        CopyTree(root->getRightSon(), new_table, new_size);
        int tmp_cell = HashFunc(root->getKey(), new_size);
        new_table[tmp_cell]->add(root->getKey(), root->getData());
    }
};

#endif //WET2_HASHTABLE_H
