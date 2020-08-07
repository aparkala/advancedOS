//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_ALGORITHM_H
#define P4_ALGORITHM_H

#include <vector>
#include "Memory.h"
#include "StatsCollector.h"

//this is the base class for all algorithms
class Algorithm {
public:
    Algorithm(std::vector<Process *> processListIn);

    //algorithm subclasses must override this method
    //expect this method to be called in every 100ms with current time in milliseconds
    void onCycle(long currentTime);
    int freePage();

    virtual int evictPage(long currentTime) = 0;

    Memory memory;
    std::vector<Process *> processList;
    int completedProcesses;


protected:


private:


};


#endif //P4_ALGORITHM_H
