//
// Created by Ozcan Ergul on 31.07.2020.
//

#include "RandomPick.h"

int RandomPick::evictPage(long currentTime){

    int evictPage;
    do{
        evictPage = rand()%FRAME_NUMBER;
    }while(this->memory.frames[evictPage].loadTime == currentTime);

    return evictPage;
}

