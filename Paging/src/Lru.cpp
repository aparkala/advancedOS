//
// Created by Ozcan Ergul on 31.07.2020.
//

#include "Lru.h"
#include "Constants.h"

int Lru::evictPage(long currentTime){
    long earliest_ref_time = 100000;
    int evictPage = -1;
    for(int i = 0; i < FRAME_NUMBER; i++){
        if(this->memory.frames[i].loadTime != -1 && this ->memory.frames[i].loadTime != currentTime && this->memory.frames[i].lastReferencedTime < earliest_ref_time){
            earliest_ref_time = this->memory.frames[i].lastReferencedTime;
            evictPage = i;
        }
    }
    return evictPage;
}