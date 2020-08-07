//
// Created by Ozcan Ergul on 31.07.2020.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include "StatsCollector.h"

using namespace std;

StatsCollector::StatsCollector() {
    missCount = 0;
    hitCount = 0;
    swappedInProcessCount = 0;
    swappedOutProcessCount = 0;
}

void StatsCollector::addProcessSwapIn(long time, Process &processSwappedIn, std::string memoryMapIn) {

    StatsItem statsItem;
    statsItem.operationType = ProcessSwapIn;
    statsItem.operationTime = time;
    statsItem.inOutPageNumber = 4;
    statsItem.processNameOfHitPage = "";
    statsItem.swappedInProcessName = getFormattedPName(processSwappedIn.processId, 3);
    statsItem.swappedOutProcessName = "";
    statsItem.evictedPageName = "";
    statsItem.memoryMap = memoryMapIn;

    missCount += 4;
    swappedInProcessCount += 1;
    statsItemList.push_back(statsItem);
}

void StatsCollector::addProcessSwapOut(long time, int swappedOutPageNumber, Process &processSwappedOut,
                                       std::string memoryMapIn) {

    StatsItem statsItem;
    statsItem.operationType = ProcessSwapOut;
    statsItem.operationTime = time;
    statsItem.inOutPageNumber = swappedOutPageNumber;
    statsItem.processNameOfHitPage = "";
    statsItem.swappedInProcessName = "";
    statsItem.swappedOutProcessName = getFormattedPName(processSwappedOut.processId, 3);
    statsItem.evictedPageName = "";
    statsItem.referencedPageName = "";
    statsItem.memoryMap = memoryMapIn;

    swappedOutProcessCount += 1;
    statsItemList.push_back(statsItem);

}

void StatsCollector::addSwap(long time, Page &pageOut, Page &pageIn, std::string memoryMapIn) {

    StatsItem statsItem;
    statsItem.operationType = PageSwap;
    statsItem.operationTime = time;
    statsItem.inOutPageNumber = 1;
    statsItem.processNameOfHitPage = "";
    statsItem.swappedInProcessName = getFormattedPName(pageIn.processId, 3);
    statsItem.referencedPageName = getFormattedPName(pageIn.pageId, 2);
    if (pageOut.processId != -1)
        statsItem.swappedOutProcessName = getFormattedPName(pageOut.processId, 3);
    else
        statsItem.swappedOutProcessName = "NULL";
    if (pageOut.processId != -1)
        statsItem.evictedPageName = getFormattedPName(pageOut.pageId, 2);
    else
        statsItem.evictedPageName = "NULL";
    statsItem.memoryMap = memoryMapIn;

    missCount += 1;
    statsItemList.push_back(statsItem);
}


void StatsCollector::addHit(long time, Page &hitPage, std::string memoryMapIn) {

    StatsItem statsItem;
    statsItem.operationType = PageHit;
    statsItem.operationTime = time;
    statsItem.inOutPageNumber = 0;
    statsItem.processNameOfHitPage = getFormattedPName(hitPage.processId, 3);
    statsItem.swappedInProcessName = "";
    statsItem.swappedOutProcessName = "";
    statsItem.referencedPageName = getFormattedPName(hitPage.pageId, 2);
    statsItem.evictedPageName = "";
    statsItem.memoryMap = memoryMapIn;

    hitCount += 1;
    statsItemList.push_back(statsItem);
}

std::string StatsCollector::getFormattedPName(int pId, int width) {

    std::ostringstream pNameStream;
    pNameStream << std::setfill('0')
                << std::setw(width) << std::right << pId;
    std::string pName;

    //this is for pages 'p' to format as "p00"
    if (width == 2) {
        pName = "p" + pNameStream.str();
    }
        //this is for processes 'P' to format as "P000"
    else {
        pName = "P" + pNameStream.str();
    }

    return pName;
}

void StatsCollector::printOperations() {

    cout << endl;
    int size = statsItemList.size();

    for (int i = 0; i < size; ++i) {

        printf("Event Time: %.2f\n", statsItemList[i].operationTime / (float) 1000);
        switch (statsItemList[i].operationType) {
            case ProcessSwapIn:
                cout << "Process " << statsItemList[i].swappedInProcessName << "'s "
                     << "First 4 Pages Loaded into Memory (Process Started)\n";
                break;
            case ProcessSwapOut:
                cout << "Process " << statsItemList[i].swappedOutProcessName << "'s "
                     << statsItemList[i].inOutPageNumber << " Pages Swapped Out (Process Finished)\n";
                break;
            case PageSwap:
                cout << "Miss Occurred!\n";
                if (statsItemList[i].swappedOutProcessName.compare("NULL") != 0) {
                    cout << statsItemList[i].swappedOutProcessName << ":" << statsItemList[i].evictedPageName
                         << " swapped out\n";
                }
                cout << statsItemList[i].swappedInProcessName << ":" << statsItemList[i].referencedPageName
                     << " swapped in\n";
                break;
            case PageHit:
                cout << "Hit Occurred!\n";
                cout << statsItemList[i].processNameOfHitPage << ":" << statsItemList[i].referencedPageName
                     << " is already in memory\n";
                break;
        }
        printf("-------------------------------------------------------------------------\n");
        printf("PID : pageID : loadTime : lastReferencedTime : referenceCounter\n");
        printf("-------------------------------------------------------------------------\n");
        cout << statsItemList[i].memoryMap << endl<<endl;
    }
}

void StatsCollector::printStats() {
    cout << endl;
    cout << "Swapped In Process Count: " << swappedInProcessCount << endl;
    cout << "Swapped Out Process Count: " << swappedOutProcessCount << endl;
    cout << "Hit Count: " << hitCount << endl;
    cout << "Miss Count: " << missCount << endl;
    printf("Hit Ratio: %.4f\n", (float) hitCount / (hitCount + missCount));
}
