#include <stdio.h>
#include "SRT.h"

int getProcWithShortestRemainingTime(AlgObject *a) {
    int i, shortest = 0;
    float temp = a->started[0]->totalRunTime-a->started[0]->completedRunTime;
    float shortestVal = temp;
    for(i = 1; i < a->startedIndex; i++) {
        temp = a->started[i]->totalRunTime-a->started[i]->completedRunTime;
        if(shortestVal > temp) {
            shortestVal = temp;
            shortest = i;
        }
    }
    return shortest;
}

void doSRT(ProcInfo *procs, int numProcs) {
    // sjp = index to shortestJobProcess in a->started
    int sjp;
    AlgObject *a = createAlgObject(procs, numProcs);

    printf("Starting shortest remaining time algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    first100Preemptive(a);

    while(a->startedIndex > 0) {
        // there are some processes that need to finish executing
        sjp = getProcWithShortestRemainingTime(a);
        giveQuantaPremptive(a, sjp);
    }
    printResults(a);
    cleanupAlgObject(a);
}
