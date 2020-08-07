//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_MEMORY_H
#define P4_MEMORY_H

#include "Page.h"
#include "Process.h"
#include "StatsCollector.h"
#include "Constants.h"

class Memory {
private:

    bool isInitialLoad;
    void copyPage(Page &copyFrom, Page &copyTo);

public:
    Memory();
    std::string getMemoryMap();
    bool initialLoad(Process &processToLoad, std::vector<Process*> &processList, long currentTime);

    bool getPage(Page &page, Process& process, long currentTime);

    void swapPages(int pageOutIndex,Page& pageOut, Page& pageIn, Process &process, std::vector<Process*> &processList, long currentTime);

    void releaseAllPages(Process &processToRelease, long currentTime);

    //all frames' pageId is -1 initially, thus is means frame is empty
    Page frames[FRAME_NUMBER];
    StatsCollector stats;

};


#endif //P4_MEMORY_H
