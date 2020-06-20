#include <iostream>
#include "library2.h"
#include "MusicManager.h"
#include <stdlib.h>

int main() {
  void *music_manager = Init();
  MusicManager *ds = (MusicManager *) music_manager;
  ds->AddArtist(1);
  for (int i = 1; i <= 15; ++i) {
    ds->AddSong(1, i);
    ds->AddToSongCount(1, i, rand() % 100);
  }
  int artist, song;
  ds->GetArtistBestSong(1, &song);
  Quit(&music_manager);

  return 0;
}
