//
// Created by Ozcan Ergul on 31.07.2020.
//

#include "Mfu.h"

int Mfu::evictPage(long currentTime)
{
	int most_ref_time = -10;
    int evictPage = -1;

    for(int i = 0; i < FRAME_NUMBER; i++){
        if(this->memory.frames[i].loadTime != -1 && this ->memory.frames[i].loadTime != currentTime && this->memory.frames[i].referenceCounter >= most_ref_time){
            most_ref_time = this->memory.frames[i].referenceCounter;
            evictPage = i;
        }
    }
    return evictPage;
}
