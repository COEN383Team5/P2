#include <stdio.h>
#include "RR.h"
#include "AlgObject.h"

void doRR(ProcInfo *procs, int numProcs) {
    int i;
    AlgObject *a = createAlgObject(procs, numProcs);

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    first100Preemptive(a);

    while(a->startedIndex > 0) {
        // there are some processes that need to finish executing
        for(i = 0; i < a->startedIndex; i++) {
            giveQuantaPremptive(a, i);
        }
    }
    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
