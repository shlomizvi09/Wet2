//
// Created by Arik on 19/06/2020.
//

#include "library2.h"
#include "MusicManager.h"

void *Init() {
    try {
        MusicManager *DS = new MusicManager();
        return (void *) DS;
    }
    catch (...) {
        return nullptr;
    }
}

StatusType AddArtist(void *DS, int artistID) {
    if (DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *) DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->AddArtist(artistID);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_EXISTS)
        return FAILURE;
    if (tmpResult == MM_SUCCESS)
        return SUCCESS;
    return FAILURE;
}

StatusType RemoveArtist(void *DS, int artistID) {
    if (DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *) DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->RemoveArtist(artistID);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_NOT_EXISTS)
        return FAILURE;
    return SUCCESS;
}

StatusType AddSong(void *DS, int artistID, int songID) {
    if (songID <= 0 || DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *) DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->AddSong(artistID, songID);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_EXISTS || tmpResult == MM_FAIL)
        return FAILURE;
    return SUCCESS;
}

StatusType RemoveSong(void *DS, int artistID, int songID) {
    if (songID <= 0 || DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *) DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->RemoveSong(artistID, songID);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_NOT_EXISTS || tmpResult == MM_FAIL)
        return FAILURE;
    return SUCCESS;
}

StatusType AddToSongCount(void *DS, int artistID, int songID, int count) {
    if (DS == nullptr)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *) DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->AddToSongCount(artistID, songID, count);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_NOT_EXISTS || tmpResult == MM_FAIL)
        return FAILURE;
    if (tmpResult == MM_INVALID_INPUT)
        return INVALID_INPUT;
    return SUCCESS;
}


void Quit(void **DS) {
    MusicManager *ds = (MusicManager *) *DS;
    ds->DeleteMM();
    delete ds;
    *DS = nullptr;


}





