#include <stdio.h>
#include "FCFS.h"
#include "AlgObject.h"

void doFCFS(ProcInfo *procs, int numProcs) {
    int i;
    AlgObject *a = createAlgObject(procs, numProcs);

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    first100NonPreemptive(a);

    while(a->startedIndex > 0) {
        // there are some processes that need to finish executing
        for(i = 0; i < a->startedIndex; i++) {
            giveQuantaNonPremptive(a, i);
        }
    }
    printResults(a);
    cleanupAlgObject(&a);
}
