//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_FIFO_H
#define P4_FIFO_H

#include <vector>
#include "Algorithm.h"

class Fifo : public Algorithm {
public:
    Fifo(std::vector<Process*> processList) : Algorithm(processList) {
    }

    int evictPage(long currentTime) override;

};


#endif //P4_FIFO_H
