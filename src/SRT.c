#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "SRT.h"

void doSRT(ProcInfo *procs, int numProcs) {
    Stack *preemptedProcs;
    int timeChart[10240];
    ProcInfo *temp, *curRun = NULL, procCopy[numProcs];
    ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    int finishedIndex = 0, nextProc = 0, curTime = 0, chartIndex = 0;

    memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));
    preemptedProcs = initializeStack();

    printf("Starting shortest remaining time algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    // only quit when there are not more processes to run
    while(1) {
        if(curTime < desiredQuanta && nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
            if(curRun != NULL 
                    && procCopy[nextProc].totalRunTime < curRun->totalRunTime-curRun->completedRunTime
              ) {
                curRun->timesWaited++;
                addToStack(preemptedProcs, curRun);
                
                printf("%d was preempted by %d\n", curRun->id, procCopy[nextProc].id);
                curRun = &procCopy[nextProc++];
                timeChart[chartIndex++] = curRun->id;
            } else {
                addToStack(preemptedProcs, &procCopy[nextProc++]); 
            }
        }
        if(curRun == NULL) {
            if((temp = getSmallestRemainingTimeOnStack(preemptedProcs)) != NULL) {
                curRun = temp;
                temp = NULL;
            } else if((curRun = getSmallestRemainingTimeOnStack(preemptedProcs)) == NULL && curTime > desiredQuanta) {
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
            }
        } else {
            fprintf(stderr, "Processor was unused during %d quantum\n", curTime);
        }

        curTime++;
    }

    printResults(finished, finishedIndex, timeChart, chartIndex, numProcs, curTime);
    // cleanupStack(preemptedProcs);
    // preemptedProcs = NULL;
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    free(finished);
    finished = NULL;
}
