//
// Created by Arik on 15/06/2020.
//

#ifndef WET2_MUSICMANAGER_H
#define WET2_MUSICMANAGER_H

#include "HashTable.h"
#include "AVLTree.h"

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

class DegTreeNodeData;

class FirstTreeNodeData {
    AVLTree<SecondTreeNodeData, SecondTreeNodeData *> *tree;
    TreeNode<SecondTreeNodeData, SecondTreeNodeData *> *smallest;

public:
    FirstTreeNodeData() : tree(nullptr), smallest(nullptr) {};

    ~FirstTreeNodeData() = default;

    AVLTree<SecondTreeNodeData, SecondTreeNodeData *> getData() {
        return *tree;
    }

    TreeNode<SecondTreeNodeData, SecondTreeNodeData *> getBestSong() {
        return *smallest;
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

class DegTreeNodeData {
    int plays;
    int singerID;
    int songID;
public:
    DegTreeNodeData(int plays, int singerID, int songID) : plays(plays), singerID(singerID), songID(songID) {};

    ~DegTreeNodeData() = default;

    int getPlays() const {
        return plays;
    }

    int getSingerID() const {
        return singerID;
    }

    int getSongID() const {
        return songID;
    }

    bool operator==(DegTreeNodeData other) const {
        return (this->plays == other.plays && this->singerID == other.singerID && this->songID == other.songID);
    }

    bool operator<(DegTreeNodeData other) const {
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


#endif //WET2_MUSICMANAGER_H
