//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_STATSCOLLECTOR_H
#define P4_STATSCOLLECTOR_H

#include <vector>
#include <string>
#include "Page.h"
#include "Process.h"

//TODO
class StatsCollector {
public:
    StatsCollector();
    void addProcessSwapIn(long time, Process &processSwappedIn, std::string memoryMapIn);
    void addProcessSwapOut(long time, int swappedOutPageNumber, Process &processSwappedOut, std::string memoryMapIn);
    void addSwap(long time, Page &pageOut, Page &pageIn, std::string memoryMapIn);
    void addHit(long time, Page &hitPage, std::string memoryMapIn);
    void printOperations();
    void printStats();
    long missCount, hitCount, swappedInProcessCount, swappedOutProcessCount;
private:


    enum OperationType {
        ProcessSwapIn, ProcessSwapOut, PageSwap, PageHit
    };

    struct StatsItem {
        OperationType operationType;
        long operationTime;
        int inOutPageNumber;
        std::string processNameOfHitPage;
        std::string swappedInProcessName;
        std::string swappedOutProcessName;
        std::string referencedPageName;
        std::string evictedPageName;
        std::string memoryMap;
    };

    std::vector<StatsItem> statsItemList;
    std::string getFormattedPName(int pId, int width);


};


#endif //P4_STATSCOLLECTOR_H
