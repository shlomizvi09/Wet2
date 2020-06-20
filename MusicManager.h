//
// Created by Arik on 15/06/2020.
//

#ifndef WET2_MUSICMANAGER_H
#define WET2_MUSICMANAGER_H

#include "HashTable.h"

#include "library2.h"

typedef enum MusicManagerResult {
  MM_SUCCESS,
  MM_EXISTS,
  MM_NOT_EXISTS,
  MM_INVALID_INPUT,
  MM_NULL_ARGUMENT,
  MM_FAIL
} MusicManagerResult;

class MusicManager;

class FirstTreeNodeData;

class SecondTreeNodeData;

class ThirdTreeNodeData;

class FirstTreeNodeData {
  AVLRankTree<SecondTreeNodeData, SecondTreeNodeData *> *tree; // Second type song tree //
  AVLRankTree<int, SecondTreeNodeData *> *aux_tree;            // Second type aux song tree //

 public:
  FirstTreeNodeData() {
    tree = new AVLRankTree<SecondTreeNodeData, SecondTreeNodeData *>();
    aux_tree = new AVLRankTree<int, SecondTreeNodeData *>();
  };

  ~FirstTreeNodeData() {
    delete tree;
    delete aux_tree;
  };

  AVLRankTree<SecondTreeNodeData, SecondTreeNodeData *> *getTree() {
    return tree;
  }

  AVLRankTree<int, SecondTreeNodeData *> *getAuxTree() {
    return aux_tree;
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
  }

  void addToPlays(int count) {
    this->plays += count;
  }

  bool operator==(SecondTreeNodeData other) const {
    return (this->songID == other.songID && this->plays == other.plays);
  }

  bool operator<(SecondTreeNodeData other) const {
    if (this->plays > other.plays)
      return true;
    if (this->plays < other.plays)
      return false;
    if (this->plays == other.plays)
      return (this->songID < other.songID);
  }

  bool operator>(SecondTreeNodeData other) const {
    if (this->plays < other.plays)
      return true;
    if (this->plays > other.plays)
      return false;
    if (this->plays == other.plays)
      return (this->songID > other.songID);
    return false;
  }
};

class ThirdTreeNodeData {
  int plays;
  int singerID;
  int songID;
 public:
  ThirdTreeNodeData(int plays, int singerID, int songID)
      : plays(plays), singerID(singerID), songID(songID) {};

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

  void addToPlays(int count) {
    this->plays += count;
  }

  bool operator==(ThirdTreeNodeData other) const {
    return (this->plays == other.plays && this->singerID == other.singerID
        && this->songID == other.songID);
  }

  bool operator<(ThirdTreeNodeData other) const {
    if (this->plays > other.plays)
      return true;
    if (this->plays < other.plays)
      return false;
    if (this->plays == other.plays) {
      if (this->singerID < other.singerID)
        return true;
      if (this->singerID > other.singerID)
        return false;
      if (this->singerID == other.singerID)
        return (this->songID < other.songID);
    }
  }

  bool operator>(ThirdTreeNodeData other) const {
    if (this->plays < other.plays)
      return true;
    if (this->plays > other.plays)
      return false;
    if (this->plays == other.plays) {
      if (this->singerID > other.singerID)
        return true;
      if (this->singerID < other.singerID)
        return false;
      if (this->singerID == other.singerID)
        return (this->songID > other.songID);
    }
    return false;
  }
};

class MusicManager {
  HashTable<int, FirstTreeNodeData *> *hash_table;
  AVLRankTree<ThirdTreeNodeData, ThirdTreeNodeData *> *rank_songs_tree;
 public:
  MusicManager() {
    hash_table = new HashTable<int, FirstTreeNodeData *>();
    rank_songs_tree = new AVLRankTree<ThirdTreeNodeData, ThirdTreeNodeData *>();
  }

  ~MusicManager() {
    delete hash_table;
    delete rank_songs_tree;
  }

  MusicManagerResult AddArtist(int artistID);

  MusicManagerResult RemoveArtist(int artistID);

  MusicManagerResult AddSong(int artistID, int songID);

  MusicManagerResult RemoveSong(int artistID, int songID);

  void DeleteMM();

  void DeleteDegTreeData(TreeNode<ThirdTreeNodeData, ThirdTreeNodeData *> *root);

  void DeleteSingerTreeData(TreeNode<SecondTreeNodeData, SecondTreeNodeData *> *root);

  void DeleteSingerAuxTreeData(TreeNode<int, SecondTreeNodeData *> *root);

  void PatrolSingersTree(TreeNode<int, FirstTreeNodeData *> *root);

  MusicManagerResult AddToSongCount(int artistID, int songID, int count);

  MusicManagerResult GetArtistBestSong(int artistID, int *songId);

  MusicManagerResult GetRecommendedSongInPlace(int rank, int *artistId, int *songId);

};

#endif //WET2_MUSICMANAGER_H
