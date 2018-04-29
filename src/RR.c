#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RR.h"
#include "Stack.h"
#include "Queue.h"

void doRR(ProcInfo *procs, int numProcs) {
    Queue *rrQ;
    Stack *preemptedProcs;
    ProcInfo procCopy[numProcs], *temp, *curRun = NULL;
    ProcInfo **finished = (ProcInfo **)calloc(numProcs, sizeof(ProcInfo*));
    int timeChart[TIME_CHART_SIZE], curTime = 0, chartIndex = 0, finishedIndex = 0, nextProc = 0;

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    preemptedProcs = initializeStack();
    
    memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));
    rrQ = initializeQueue();

    // only quit when there are not more processes to run
    while(1) {
        if(curTime < desiredQuanta && nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
            if(curRun != NULL 
                && procCopy[nextProc].totalRunTime < curRun->totalRunTime-curRun->completedRunTime
              ) { 
              // preempting
                curRun->timesWaited++;
                addToStack(preemptedProcs, curRun);
                printf("%d was preempted by %d\n", curRun->id, procCopy[nextProc].id);
                curRun = &procCopy[nextProc++];
                timeChart[chartIndex++] = curRun->id;
            } else {
                addToQueue(rrQ, &procCopy[nextProc++]); 
            }
        }
        if(curRun == NULL) {
            // need to select a new process to run
            if((temp = popStack(preemptedProcs)) != NULL) {
                // run the preempted procs
                curRun = temp;
                temp = NULL;
            } else if((curRun = pop(rrQ)) == NULL && curTime > desiredQuanta) {
                // no more procs to run
                break;
            }
        }
        if(curRun != NULL) {
            timeChart[chartIndex++] = curRun->id;
            giveQuantaToProc(curRun, curTime);
            if(curRun->completedRunTime > curRun->totalRunTime) {
                finished[finishedIndex++] = curRun;
                curRun = NULL;
            } else {
                addToQueue(rrQ, curRun);
                curRun = NULL;
            }
        } else {
            fprintf(stderr, "Processor was unused during %d quantum\n", curTime);
        }
        curTime++;
    }

    printResults(finished, finishedIndex, timeChart, chartIndex, numProcs, curTime);
    cleanupStack(preemptedProcs);
    preemptedProcs = NULL;
    free(finished);
    finished = NULL;
    cleanupQueue(rrQ);
    rrQ = NULL;
}
