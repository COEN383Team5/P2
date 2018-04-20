#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HPF.h"
#include "Stack.h"

#define AGING_TIME 5

void adjustPriorities(PriorityQueue *pq, int curTime) {
    int i;
    ProcInfo *p;
    for(i = 0; i < pq->numInQueues; i++) {
        p = getNextProc(pq);
        if(curTime-p->lastRunTime >  AGING_TIME && p->priority != 1) {
                p->priority--;
        }
        addProc(pq, p);
    }
}

void doHPF(ProcInfo *procs, int numProcs, int preemptive, int aging) {
    Stack *preemptedProcs;
    int timeChart[TIME_CHART_SIZE];
    ProcInfo *temp, *curRun = NULL, procCopy[numProcs];
    ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    int finishedIndex = 0, nextProc = 0, curTime = 0, chartIndex = 0;
    PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

    memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));
    preemptedProcs = initializeStack();

    printf("Starting highest priority first algorithm");
    if(preemptive) {
        printf(" with preemption\n\n");
    } else {
        printf(" without preemption\n\n");
    }
    printProcs(procs, numProcs, stdout);

    // only quit when there are not more processes to run
    while(1) {
        if(curTime < desiredQuanta && nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
            if(preemptive && curRun != NULL 
                    && procCopy[nextProc].totalRunTime < curRun->totalRunTime-curRun->completedRunTime
                    && procCopy[nextProc].priority < curRun->priority
              ) {
                curRun->timesWaited++;
                addToStack(preemptedProcs, curRun);
                printf("%d was preempted by %d\n", curRun->id, procCopy[nextProc].id);
                curRun = &procCopy[nextProc++];
                timeChart[chartIndex++] = curRun->id;
            } else {
                addProc(pq, &procCopy[nextProc++]); 
            }
        }
        if(curRun == NULL) {
            if((temp = popStack(preemptedProcs)) != NULL) {
                curRun = temp;
                temp = NULL;
            } else if((curRun = getNextProc(pq)) == NULL && curTime > desiredQuanta) {
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
        if(aging) {
            adjustPriorities(pq, curTime);
        }
        curTime++;
    }

    printResults(finished, finishedIndex, timeChart, chartIndex, numProcs, curTime);
    cleanupStack(preemptedProcs);
    preemptedProcs = NULL;
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    free(finished);
    finished = NULL;
    cleanupPriorityQueue(pq);
    pq = NULL;
}
