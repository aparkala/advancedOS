//
// Created by Ozcan Ergul on 31.07.2020.
//
#include <vector>
#include "Algorithm.h"
#include "Constants.h"


Algorithm::Algorithm(std::vector<Process *> processListIn) {

    processList = processListIn;
    completedProcesses = 0;
}


void Algorithm::onCycle(long currentTime) {
    std::vector<Process *>::iterator procItr;
    Page *nextPage;
    int freePage;
    int evictPage;

    //iterating through all processes
    for (procItr = this->processList.begin(); procItr != processList.end(); procItr++) {

        //running only those with arrival time<=currentTime
        if ((*procItr)->arrivalTime <= currentTime && !((*procItr)->hasFinished())) {

            //process has not started
            if (!(*procItr)->hasStarted()) {

                //load process in memory/wait for another process to finish execution
                if (this->memory.initialLoad(**procItr, processList,currentTime)) {
                    (*procItr)->remainingServiceTime -= CYCLE_IN_MS;

                } else {
                    continue;
                }
            }

                //process has already started
            else {
                nextPage = (*procItr)->getNextPage();
                if (this->memory.getPage(*nextPage, **procItr, currentTime)) {
                    //hit
                    //call hit stats method
                    //this->memory.stats->addHit(currentTime, *nextPage,memoryMap);
                } else {
                    freePage = this->freePage();

                    //memory is available
                    if (freePage >= 0) {
                        //this->memory.stats->addSwap(currentTime, this->memory.frames[freePage], *nextPage, memoryMap);
                        this->memory.swapPages(freePage,memory.frames[freePage], *nextPage,**procItr , processList, currentTime);
                    }
                        //need to evict page
                    else {
                        evictPage = this->evictPage(currentTime);
                        this->memory.swapPages(evictPage,memory.frames[evictPage], *nextPage, **procItr,processList, currentTime);
                    }
                }
                (*procItr)->remainingServiceTime -= CYCLE_IN_MS;
                if ((*procItr)->remainingServiceTime == 0) {
                    //this->memory.stats->addProcessSwapOut(currentTime,,*procItr,memoryMap);
                    this->memory.releaseAllPages(**procItr, currentTime);
                    completedProcesses++;
                }
            }
        }
    }
}

int Algorithm::freePage() {
    for (int i = 0; i < FRAME_NUMBER; i++) {
        if (this->memory.frames[i].pageId == -1) {
            return i;
        }
    }
    return -1;
}