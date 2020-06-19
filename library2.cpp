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