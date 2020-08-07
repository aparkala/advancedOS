//
// Created by Ozcan Ergul on 31.07.2020.
//

#include "Process.h"
#include <cstdlib>
#include <iostream>


Process::Process(int processIdIn) {

    processId = processIdIn;
    serviceTime = (rand() % 5 + 1) * 1000;
    remainingServiceTime = serviceTime;
    arrivalTime = (rand() % 60) * 1000;
    lastReferencedPageId = -1;

    generatePages();
    setRefString();
}

Process::Process(const Process &process) {

	this->processId = process.processId;
	this->serviceTime = process.serviceTime;
	this->remainingServiceTime = process.remainingServiceTime;
	this->arrivalTime = process.arrivalTime;
	this->lastReferencedPageId = process.lastReferencedPageId;
	// copy original generatePages()
	for (int i = 0; i < process.pageList.size(); i++) {
		Page *page_dest = new Page(*(process.pageList[i]));
		this->pageList.push_back(page_dest);
	}
}

//this method returns the next page the process makes reference
//algorithms should use this method to get the next page reference of the process
//TODO implement 70%-30% locality of reference logic
Page *Process::getNextPage() {
    Page *page;
    /*int next;
    if (lastReferencedPageId == -1) {
        next = 0;
        page = pageList[0];
    } else {
        int i = rand() % 10;

        if (i < 7) {
            int adjacentRand = rand() % 3;
            int nextRef;

            next = lastReferencedPageId + adjacentRand - 1;
            nextRef = lastReferencedPageId + adjacentRand - 1;

            if (nextRef <= 0) {
                next = 0;
                page = pageList[0];
            } else if (nextRef >= numberOfPages) {
                next = numberOfPages - 1;
                page = pageList[numberOfPages - 1];
            } else {
                page = pageList[nextRef];
        }

        } else {
            int nextRef;
            do {
                nextRef = rand() % numberOfPages;
                next = nextRef;
            } while (nextRef == lastReferencedPageId - 1 || nextRef == lastReferencedPageId ||
                     nextRef == lastReferencedPageId + 1);

            page = pageList[nextRef];
        }
    }*/

    page = pageList[refString.at(0)];
    refString.erase(refString.begin());
    return page;
}

void Process::setRefString() {
    lastReferencedPageId = 0;
    int next;
    for (int i = 0; i < (numberOfPages*10); i++){
        if (lastReferencedPageId == -1) {
            next = 0;
        } else {
            int i = rand() % 10;

            if (i < 7) {
                int adjacentRand = rand() % 3;

                next = lastReferencedPageId + adjacentRand - 1;

                if (next <= 0) {
                    next = 0;
                } else if (next >= numberOfPages) {
                    next = numberOfPages - 1;
                } else {

                }

            } else {
                do {
                    next = rand() % numberOfPages;
                } while (next == lastReferencedPageId - 1 || next == lastReferencedPageId ||
                         next == lastReferencedPageId + 1);

            }
        }
        refString.push_back(next);
    }
    lastReferencedPageId = -1;
}

//pages for the process are created in this method
void Process::generatePages() {

    int i = rand() % 4 + 1;
        switch (i) {
            case 1:
            numberOfPages = 5;
                break;
        case 2:
            numberOfPages = 11;
                break;
            case 3:
            numberOfPages = 17;
                break;
        case 4:
            numberOfPages = 31;
                break;
        }

    for (i = 0; i < numberOfPages; i++) {
        Page *p = new Page(i, processId);
        pageList.push_back(p);
    }
}

//shortcut method to check if process has already started
bool Process::hasStarted() {
    if (serviceTime > remainingServiceTime)
        return true;
    else
        return false;
}

bool Process::hasFinished() {

    if (remainingServiceTime > 0)
        return false;
    else
        return true;
}



