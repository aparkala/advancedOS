//
// Created by Ozcan Ergul on 31.07.2020.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include "Memory.h"
#include "Constants.h"


Memory::Memory() {
    isInitialLoad = false;
}

/*
 * this method is used for initial loading of the process if it has not already started
 * it returns true if it finds empty space and loads the first 4 pages of the process into the memory
 * it returns false if it cannot find any empty space in the memory
*/

//TODO implement the logic to load the first 4 pages of the process into the memory (if there is enough free space)
bool Memory::initialLoad(Process &processToLoad, std::vector<Process *> &processList, long currentTime) {
    //int freeFramesStartIndex = -1;

    bool hasFourFreeFrames = false;
    int frameIndex[4], ctr = 0;
    int numFreeFrames=0;
    for (int i = 0; i <= FRAME_NUMBER - 4; ++i) {
        if(frames[i].processId == -1) {
            numFreeFrames += 1;
            frameIndex[ctr] = i;
            ctr++;
        }

        if (numFreeFrames >= 4) {
            //freeFramesStartIndex = i;
            isInitialLoad = true;
            for (int j = 0; j < 4; ++j) {
                swapPages(frameIndex[j], (frames[frameIndex[j]]), *processToLoad.pageList[j],
                          processToLoad, processList,
                          currentTime);
            }
            isInitialLoad = false;


            Page *pageInMemory;
            Page *pageInProcess = processToLoad.pageList[0];

            for (int k = 0; k < FRAME_NUMBER; ++k) {
                if (frames[k].processId == processToLoad.processId &&
                    frames[k].pageId == processToLoad.pageList[0]->pageId) {
                    pageInMemory = &frames[k];
                }
            }

            processToLoad.lastReferencedPageId = pageInProcess->pageId;
            //pageInProcess->referencePage(currentTime);
            //pageInMemory->referencePage(currentTime);


            stats.addProcessSwapIn(currentTime, processToLoad, getMemoryMap());
            hasFourFreeFrames = true;
            break;
        }
    }

    return hasFourFreeFrames;
}

//non_consecutive version
//bool Memory::initialLoad(Process &processToLoad, long currentTime) {
//    int freeFramesIndex[4];
//    int freeFrameCounter = 0;
//    bool hasFourFreeFrames = false;
//
//    for (int i = 0; i < FRAME_NUMBER; ++i) {
//        if (frames[i].processId == -1) {
//            freeFramesIndex[freeFrameCounter++] = i;
//            if (freeFrameCounter == 4) {
//                hasFourFreeFrames = true;
//                break;
//            }
//        }
//    }
//
//    if (hasFourFreeFrames) {
//            isInitialLoad = true;
//            for (int j = 0; j < 4; ++j) {
//                swapPages(frames[freeFramesIndex[j]], *processToLoad.pageList[j], processToLoad,
//                          currentTime);
//            }
//            isInitialLoad = false;
//
//            processToLoad.lastReferencedPageId = processToLoad.pageList[0]->pageId;
//            processToLoad.pageList[0]->referencePage(currentTime);
//
//            stats.addProcessSwapIn(currentTime, processToLoad, getMemoryMap());
//        }
//
//    return hasFourFreeFrames;
//}

/*
 * this method should be called when a process wants to access a page
 * it returns true if it is already in the memory, false otherwise
 * this information can be obtained by just checking page's inMemory field
 * but algorithms should use this method for statistic purposes
*/

//TODO return page's inMemory field and call page's referencePage method if it is in the memory
bool Memory::getPage(Page &page, Process &process, long currentTime) {

    Page *pageInMemory; // = &page;
    Page *pageInProcess = &page;
    //Page *pageOutInProcess;
    //Page pageOutForStats = pageOut;
    //Page pageInForStats = pageIn;



    if (page.inMemory == true) {
        process.lastReferencedPageId = page.pageId;
        //page.referencePage(currentTime);
        //page.referenceCounter += 1;
        //page.lastReferencedTime = currentTime;
        //stats.addHit(currentTime, page, getMemoryMap());
        for ( int i = 0; i < FRAME_NUMBER; i++){
            if (frames[i].processId == page.processId && frames[i].pageId == page.pageId){
                pageInMemory = &frames[i];
            }
        }

        pageInMemory->lastReferencedTime = currentTime;
        pageInMemory->referenceCounter +=1;

        pageInProcess->lastReferencedTime = currentTime;
        pageInProcess->referenceCounter +=1;
        stats.addHit(currentTime, *pageInMemory, getMemoryMap());
        return true;
    } else {
        return false;
    }
}

/*
 * this method should be called when an algorithm wants to
 * swap out a page from memory and swap in a new page
*/

//TODO implement the necessary code to swap out the pageOut and swap in the pageIn into the memory
// if pageOut is not empty then set its inMemory field to false
// update the stats accordingly. Pass "new Page()"" to pageIn for "ending" processes
void
Memory::swapPages(int pageOutIndex, Page &pageOut, Page &pageIn, Process &process, std::vector<Process *> &processList,
                  long currentTime) {

    Page *pageInMemory = &pageOut;
    Page *pageInInProcess = &pageIn;
    Page *pageOutInProcess;
    bool freeFrameOut = false;

    if (pageOut.pageId == -1) freeFrameOut = true;
    Page pageOutForStats = *pageInMemory;
    Page pageInForStats = pageIn;

    if (pageOut.pageId != -1) {
        for (int i = 0; i < processList.size(); ++i) {
            for (int j = 0; j < processList[i]->pageList.size(); ++j) {
                if (processList[i]->pageList[j]->processId == pageOut.processId &&
                    processList[i]->pageList[j]->pageId == pageOut.pageId) {
                    pageOutInProcess = processList[i]->pageList[j];
            }
        }
    }

        pageOutInProcess->resetFields();
    }

    //if (isInitialLoad) {
        pageInMemory->pageId = pageInInProcess->pageId;
        pageInMemory->processId = pageInInProcess->processId;
        //pageInMemory->inMemory = true;
        //pageInInProcess->inMemory = true;
        //pageInMemory->loadTime = currentTime;
        //pageInInProcess->loadTime = currentTime;



        process.lastReferencedPageId = pageInInProcess->pageId;
        pageInMemory->loadTime = currentTime;
        pageInMemory->referenceCounter = 0;
        pageInMemory->referencePage(currentTime);
        pageInInProcess->referencePage(currentTime);

    if (!isInitialLoad) {
        stats.addSwap(currentTime, pageOutForStats, pageInForStats, getMemoryMap());
        //if (freeFrameOut) stats.addSwap(currentTime, *(new Page()), pageIn, getMemoryMap());
        //else stats.addSwap(currentTime, pageOut, pageIn, getMemoryMap());
    }
}

//    void
//    Memory::swapPages(int pageOutIndex, Page &pageOut, Page &pageIn, Process &process, std::vector<Process *> &processList,
//                      long currentTime) {
//
//        Page pageOutForStats = pageOut;
//        Page pageInForStats = pageIn;
//
//
//        if (pageOut.pageId != -1) {
//            for (int j = 0; j < processList.size(); ++j) {
//                for (int i = 0; i < processList[j]->numberOfPages; ++i) {
//                    if (processList[j]->pageList[i]->pageId == pageOut.pageId &&
//                        processList[j]->pageList[i]->processId == pageOut.processId) {
//                        processList[j]->pageList[i]->resetFields();
//                        break;
//                    }
//                }
//            }
//        }
//
//        frames[pageOutIndex] = pageIn;
//        //pageOut = pageIn;
//
//
//        if (!isInitialLoad) {
//            pageOut.referencePage(currentTime);
//            pageIn.referencePage(currentTime);
//            stats.addSwap(currentTime, pageOutForStats, pageInForStats, getMemoryMap());
//            process.lastReferencedPageId = pageIn.pageId;
//        } else {
//            pageIn.inMemory = true;
//            pageOut.inMemory = true;
//            pageIn.loadTime = currentTime;
//            pageOut.loadTime = currentTime;
//        }


//    pageOut.resetFields();
//    if (!isInitialLoad) {
//        pageIn.referencePage(currentTime);
//    } else {
//        pageIn.loadTime = currentTime;
//        pageIn.inMemory = true;
//    }
//    pageOut = pageIn;
//    frames[frameIndex] = pageOut;
//}

void Memory::releaseAllPages(Process &processToRelease, long currentTime) {

    int swappedOutPageNumber = 0;
    for (int i = 0; i < processToRelease.pageList.size(); ++i) {

        processToRelease.pageList[i]->resetFields();

        for (int j = 0; j < FRAME_NUMBER; ++j) {
            if (frames[j].pageId == processToRelease.pageList[i]->pageId &&
                frames[j].processId == processToRelease.pageList[i]->processId) {
                frames[j] = *(new Page());
                swappedOutPageNumber++;
            }
        }
    }

    stats.addProcessSwapOut(currentTime, swappedOutPageNumber, processToRelease, getMemoryMap());
}


std::string Memory::getMemoryMap() {
    std::ostringstream memoryMapStream;
    memoryMapStream << "|";

    for (int i = 0; i < FRAME_NUMBER; ++i) {
        if (frames[i].processId != -1) {
            memoryMapStream << "P" << std::setfill('0') << std::setw(3) << std::right << frames[i].processId
                            << ":" << "p" << std::setfill('0') << std::setw(2) << std::right << frames[i].pageId
                            << ":"<<frames[i].loadTime
                            <<":"<<frames[i].lastReferencedTime
                            <<":"<<frames[i].referenceCounter<<"|";
        } else {
            memoryMapStream << "----:---:-----:-----:--|";
        }
    }
    return memoryMapStream.str();
}

