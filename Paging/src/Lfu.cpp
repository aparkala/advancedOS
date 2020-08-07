//
// Created by Ozcan Ergul on 31.07.2020.
//

#include "Lfu.h"
#include "Constants.h"

int Lfu::evictPage(long currentTime)
{
	long least_ref_time = this->memory.frames[0].referenceCounter;
    int evictPage = -1;

    for(int i = 0; i < FRAME_NUMBER; i++){
        if(this->memory.frames[i].loadTime != -1 && this ->memory.frames[i].loadTime != currentTime && this->memory.frames[i].referenceCounter <= least_ref_time){
            least_ref_time = this->memory.frames[i].referenceCounter;
            evictPage = i;
        }
    }
    return evictPage;
}



