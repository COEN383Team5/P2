#include <stdio.h>
#include "FCFS.h"
#include "AlgObject.h"

void doFCFS(ProcInfo *procs, int numProcs) {
    AlgObject *a = createAlgObject(procs, numProcs);

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    // TODO

    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
