//
// Created by Ozcan Ergul on 31.07.2020.
//

#ifndef P4_RANDOMPICK_H
#define P4_RANDOMPICK_H

#include <vector>
#include "Algorithm.h"

class RandomPick: public Algorithm {

public:
    RandomPick(std::vector<Process*> processList) : Algorithm(processList) {
        srand(time(NULL));
    };

    int evictPage(long currentTime) override;

};


#endif //P4_RANDOMPICK_H
