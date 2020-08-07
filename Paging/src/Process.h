//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_PROCESS_H
#define P4_PROCESS_H

#include <vector>
#include "Page.h"

class Process {
private:
    void generatePages();

public:
    Process(int processIdIn);
	Process( const Process &process);
    Page* getNextPage();
    void setRefString();
    bool hasStarted();
    bool hasFinished();

    int processId;

    //in milliseconds
    long arrivalTime;

    //in milliseconds
    long serviceTime;

    //in milliseconds
    long remainingServiceTime;

    //each page 1MB
    int numberOfPages;

    int lastReferencedPageId;
    std::vector<Page*> pageList;
    std::vector<int> refString;



};


#endif //P4_PROCESS_H
