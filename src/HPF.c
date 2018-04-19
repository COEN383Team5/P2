#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HPF.h"

#define AGING_TIME 5

void giveQuantaToProc(ProcInfo *proc, int curTime) {
    if(proc->completedRunTime == 0) {
        proc->totalWaitTime += curTime-proc->arrivalTime;
        proc->startTime = curTime;
        proc->responseTime = proc->totalWaitTime;
    }
    proc->completedRunTime++;
    proc->lastRunTime = curTime;
}

void adjustPriorities(PriorityQueue **pq, int curTime) {
    int i;
    ProcInfo *p;
    for(i = 0; i < numInQueues; i++) {
        p = getNextProc(pq);
        if(curTime-p->lastRunTime >  AGING_TIME && p->priority != 1) {
                p->priority--;
        }
        addProc(pq, p);
    }
}

void doHPF(ProcInfo *procs, int numProcs, int preemptive, int aging) {
	RunInfo *ri;
	float timeLeft;
    bool done = false;
	ProcInfo *curRun = NULL, *procCopy = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
	ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
	int finishedIndex = 0, nextProc = 0, curTime = 0;
	PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

	memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));

	printf("Starting highest priority first algorithm");
    if(preemptive) {
        printf(" with preemption\n\n");
    } else {
        printf(" without preemption\n\n");
    }
	printProcs(procs, numProcs, stdout);
    
    while(!done) {
        curTime++;
        if(curTime < desiredQuanta && nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
           addProc(&pq, &procCopy[nextProc++]); 
        }
        if(curRun == NULL) {
            if((curRun = getNextProc(&pq)) == NULL) {
                done = true;
                break;
            }
        }
        if(curRun != NULL) {
            giveQuantaToProc(curRun, curTime);
            if(curRun->completedRunTime > curRun->totalRunTime) {
                finished[finishedIndex++] = curRun;
                curRun = NULL;
            }
        } else {
            fprintf(stderr, "Processor was unused during %d quantum\n", curTime);
        }
        if(aging) {
            adjustPriorities(&pq, curTime);
        }
    }

    printResults(finished, finishedIndex, ri->timeChart, ri->iters, numProcs, ri->runTime);
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    free(finished);
	cleanupPriorityQueue(&pq);
	pq = NULL;
	free(procCopy);
	procCopy = NULL;
}
