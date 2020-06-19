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
    if(tmpResult==MM_SUCCESS)
        return SUCCESS;
    return FAILURE;
}

StatusType RemoveArtist(void *DS, int artistID){
    if(DS== nullptr || artistID<=0)
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



