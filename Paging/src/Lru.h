//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_LRU_H
#define P4_LRU_H

#include <vector>
#include "Algorithm.h"

class Lru : public Algorithm {
public:
    Lru(std::vector<Process*> processList) : Algorithm(processList) {
    };

    int evictPage(long currentTime) override;
};


#endif //P4_LRU_H
