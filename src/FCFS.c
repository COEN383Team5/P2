#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FCFS.h"
#include "AlgObject.h"

void doFCFS(ProcInfo *procs, int numProcs) {
    int i;
    AlgObject *a = createAlgObject(procs, numProcs);

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    first100NoPrempt(a);

    while(a->startedIndex > 0) {
        // there are some processes that need to finish executing
        for(i = 0; i < a->startedIndex; i++) {
            giveQuanta(a, i);
            a->timeChart[a->timeChartIndex++] = a->started[i]->id;
            a->started[i]->completedRunTime++;
            a->started[i]->totalWaitTime += a->timeChartIndex-a->started[i]->lastRunTime;
            a->started[i]->lastRunTime = a->timeChartIndex;
            if(a->started[i]->totalRunTime <= a->started[i]->completedRunTime) {
                // this process has finished so remove it from started
                // without messing up the order of started
                a->finished[a->finishedIndex++] = a->started[i];
                if(i+1 < a->startedIndex) {
                    memmove(&a->started[i], &a->started[i+1],a->startedIndex-(i+1));
                }
                a->started[--a->startedIndex] = 0;
            }
        }
    }
    printResults(a);
    cleanupAlgObject(a);
}
