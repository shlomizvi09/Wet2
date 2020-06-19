//
// Created by Arik on 15/06/2020.
//

#ifndef WET2_MUSICMANAGER_H
#define WET2_MUSICMANAGER_H

#include "HashTable.h"
#include "AVLTree.h"
#include "AVLRankTree.h"
#include "library2.h"

typedef enum MusicManagerResult {
    MM_SUCCESS,
    MM_EXISTS,
    MM_NOT_EXISTS,
    MM_NULL_ARGUMENT,
    MM_FAIL
} MusicManagerResult;

class MusicManager;

class FirstTreeNodeData;

class SecondTreeNodeData;

class ThirdTreeNodeData;

class FirstTreeNodeData {
    AVLRankTree<SecondTreeNodeData, SecondTreeNodeData *> *tree;

public:
    FirstTreeNodeData() : tree(nullptr){};

    ~FirstTreeNodeData() = default;

    AVLRankTree<SecondTreeNodeData, SecondTreeNodeData *> getData() {
        return *tree;
    }

};

class SecondTreeNodeData {
    int plays;
    int songID;
public:
    explicit SecondTreeNodeData(int songID) : plays(0), songID(songID) {};

    SecondTreeNodeData(int plays, int songID) : plays(plays), songID(songID) {};

    ~SecondTreeNodeData() = default;

    int getPlays() const {
        return plays;
    }

    int getSongID() const {
        return songID;
    };

    bool operator==(SecondTreeNodeData other) const {
        return (this->songID == other.songID && this->plays == other.plays);
    }

    bool operator<(SecondTreeNodeData other) const {
        if (this->plays > other.plays)
            return true;
        if (this->plays == other.plays)
            return (this->songID < other.songID);
    }
};

class ThirdTreeNodeData {
    int plays;
    int singerID;
    int songID;
public:
    ThirdTreeNodeData(int plays, int singerID, int songID) : plays(plays), singerID(singerID), songID(songID) {};

    ~ThirdTreeNodeData() = default;

    int getPlays() const {
        return plays;
    }

    int getSingerID() const {
        return singerID;
    }

    int getSongID() const {
        return songID;
    }

    bool operator==(ThirdTreeNodeData other) const {
        return (this->plays == other.plays && this->singerID == other.singerID && this->songID == other.songID);
    }

    bool operator<(ThirdTreeNodeData other) const {
        if (this->plays > other.plays)
            return true;
        if (this->plays == other.plays) {
            if (this->singerID < other.singerID)
                return true;
            if (this->singerID == other.singerID)
                return (this->songID < other.songID);
        }
    }
};

class MusicManager{
    HashTable<int, FirstTreeNodeData*> *table;
    AVLRankTree<ThirdTreeNodeData,ThirdTreeNodeData*> *deg_tree;
public:
    MusicManager(){
        table = new HashTable<int, FirstTreeNodeData*>();
        deg_tree = new AVLRankTree<ThirdTreeNodeData,ThirdTreeNodeData*>();
    }

    ~MusicManager(){
        delete table;
        delete deg_tree;
    }


};



#endif //WET2_MUSICMANAGER_H