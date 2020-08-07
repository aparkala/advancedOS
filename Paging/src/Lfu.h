//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_LFU_H
#define P4_LFU_H

#include <vector>
#include "Algorithm.h"

class Lfu : public Algorithm {
public:
    Lfu(std::vector<Process*> processList) : Algorithm(processList) {
    };

    int evictPage(long currentTime) override;
};


#endif //P4_LFU_H
