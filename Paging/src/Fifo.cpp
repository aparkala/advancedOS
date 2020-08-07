//
// Created by Ozcan Ergul on 31.07.2020.
//

#include "Fifo.h"
#include "Constants.h"


/*
 * this method will be called with the current time parameter in every 100ms
*/

/*TODO
 * implement the algorithm using the processList and memory fields
 * iterate through the processList to take necessary actions for time = currentTime
 ** memory and processList fields will be already initialized before this method is called for the first time
 ** every algorithm needs to use these fields for necessary operations and update the fields accordingly
 ** check out the Algorithm base class and Memory, Process classes for details
*/

int Fifo::evictPage(long currentTime){
    long min_load_time = 100000;
    int evictPage = -1;
    for(int i = 0; i < FRAME_NUMBER; i++){
        if(this->memory.frames[i].loadTime != -1 && this ->memory.frames[i].loadTime != currentTime && this->memory.frames[i].loadTime < min_load_time){
            min_load_time = this->memory.frames[i].loadTime;
            evictPage = i;
        }
    }
    return evictPage;
}