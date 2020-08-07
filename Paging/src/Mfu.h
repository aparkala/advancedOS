//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_MFU_H
#define P4_MFU_H

#include <vector>
#include "Algorithm.h"

class Mfu : public Algorithm {
public:
    Mfu(std::vector<Process*> processList) : Algorithm(processList) {
    };

    int evictPage(long currentTime) override;
};


#endif //P4_MFU_H
