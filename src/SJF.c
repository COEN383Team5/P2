#include <stdio.h>
#include "SJF.h"

int getProcWithShortestJob(AlgObject *a) {
    int i, shortest = 0;
    float temp = a->started[0]->totalRunTime;
    float shortestVal = temp;
    for(i = 1; i < a->startedIndex; i++) {
        temp = a->started[i]->totalRunTime;
        if(shortestVal > temp) {
            shortestVal = temp;
            shortest = i;
        }
    }
    return shortest;
}

void doSJF(ProcInfo *procs, int numProcs) {
    // sjp = index to shortestJobProcess in a->started
    int sjp;
    AlgObject *a = createAlgObject(procs, numProcs);

    printf("Starting shortest job first algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    first100NonPreemptive(a);

    while(a->startedIndex > 0) {
        // there are some processes that need to finish executing
        sjp = getProcWithShortestJob(a);
        giveQuantaNonPremptive(a, sjp);
    }
    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
