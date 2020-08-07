#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h>
#include "Memory.h"
#include "Fifo.h"
#include "Lru.h"
#include "Lfu.h"
#include "Mfu.h"
#include "RandomPick.h"
#include "Constants.h"


using namespace std;

std::vector<Process*> generateProcess(int seed){
    srand(seed);
    std::vector<Process*> processList;
    for (int i = 0; i < PROCESS_NUMBER; i++){
        processList.push_back(new Process(i));
    }
    return processList;
}


int main() {

    srand(time(NULL));

    cout << endl;


    float totalHit[5];
    float totalMiss[5];
    float hitOverTotalRef[5];
    long totalProcessSwappedIn[5];
    long totalProcessSwappedOut[5];
    int totalCompletedProcesses[5];

    for (int j = 0; j < EXECUTION_COUNT; ++j) {
        totalHit[j] = 0;
        totalMiss[j] = 0;
        hitOverTotalRef[j] = 0;
        totalProcessSwappedIn[j] = 0;
        totalProcessSwappedOut[j] = 0;
        totalCompletedProcesses[j] = 0;
    }

    string algoNames[5] = {"FIFO", "LRU", "LFU", "MFU", "RANDOM PICK"};

	
	for (int x = 0; x < EXECUTION_COUNT; ++x) {
        std::vector<Process *> processList1;
        std::vector<Process *> processList2;
        std::vector<Process *> processList3;
        std::vector<Process *> processList4;
        std::vector<Process *> processList5;

        processList1 = generateProcess(x);
        processList2 = generateProcess(x);
        processList3 = generateProcess(x);
        processList4 = generateProcess(x);
        processList5 = generateProcess(x);


        Algorithm *algorithm[5] = {
			new Fifo(processList1),
			new Lru(processList2),
			new Lfu(processList3),
            new Mfu(processList4),
			new RandomPick(processList5)
		};

        for (long i = 0; i < 60000; i += CYCLE_IN_MS) {

            //call onCycle method of each algorithm
            for (int j = 0; j < 5; j++) {
                algorithm[j]->onCycle(i);
            	//std::cout << "trying alg" << '\n';
			}
        }
//        //use the stats here
        cout << endl << x+1 << ". Execution" << endl;

        for (int l = 0; l < 5; ++l) {
            algorithm[l]->memory.stats.printOperations();
            algorithm[l]->memory.stats.printStats();
            cout << endl;

            totalHit[l] += algorithm[l]->memory.stats.hitCount;
            totalMiss[l] += algorithm[l]->memory.stats.missCount;
            hitOverTotalRef[l] += (algorithm[l]->memory.stats.hitCount 
									/ (float) (algorithm[l]->memory.stats.hitCount +
                                        algorithm[l]->memory.stats.missCount));

            totalProcessSwappedOut[l] += algorithm[l]->memory.stats.swappedOutProcessCount;
            totalProcessSwappedIn[l] += algorithm[l]->memory.stats.swappedInProcessCount;
            totalCompletedProcesses[l] += algorithm[l]->completedProcesses;
    }
    }

    cout << endl << endl << endl;
    for (int i = 0; i < 100; ++i) {
        cout << "-";
    }

    cout << endl << endl;
    cout << " AVERAGE STATS OVER " << EXECUTION_COUNT << " RUNS: \n" << endl;
    for (int i = 0; i < 100; ++i) {
        cout << "-";
    }
    for (int m = 0; m < 5; ++m) {
        cout << endl;
        cout << algoNames[m]<< ":\n";
        cout << "HIT COUNT: " << totalHit[m]/EXECUTION_COUNT << endl;
        cout << "MISS COUNT: " << totalMiss[m]/EXECUTION_COUNT << endl;
        cout << "HIT RATIO: " << hitOverTotalRef[m]/EXECUTION_COUNT << endl;
        //cout << "TOTAL PROCESSES COMPLETED: " << totalCompletedProcesses[m]<< endl;
        //cout << "TOTAL SWAPPED IN PROCESSES: " << totalProcessSwappedIn[m] << endl;
        //cout << "TOTAL SWAPPED OUT PROCESSES: " << totalProcessSwappedOut[m] << endl;


    }

//    cout << endl;
//    printf("FIFO hit ratio: %.4f\n", totalHit[0] / (float) (totalHit[0] + totalMiss[0]));
//    printf("LRU hit ratio: %.4f", totalHit[1] / (float) (totalHit[1] + totalMiss[1]));
    return 0;
}
