#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HPF.h"

void giveQuantaToProc(ProcInfo *proc, int curTime) {
    if(proc->completedRunTime == 0) {
        proc->totalWaitTime += curTime-proc->arrivalTime;
        proc->startTime = curTime;
        proc->responseTime = proc->totalWaitTime;
    }
    proc->completedRunTime++;
}

void doHPF(ProcInfo *procs, int numProcs, int preemptive) {
    Queue PreemptedProcs;
    int timeChart[10240];
	ProcInfo *temp, *curRun = NULL, *procCopy = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
	ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
	int finishedIndex = 0, nextProc = 0, curTime = 0;
	PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

	memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));
    preemptedProcs = initializeQueue();

	printf("Starting highest priority first algorithm");
    if(preemptive) {
        printf(" with preemption\n\n");
    } else {
        printf(" without preemption\n\n");
    }
	printProcs(procs, numProcs, stdout);
    
    // only quit when there are not more processes to run
    while(true) {
        if(curTime < desiredQuanta && nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
            if(preemptive && curRun != NULL 
                && procCopy[nextProc].totalRunTime < curRun->totalRunTime-curRun->completedRunTime) {
                addToQueue(&preemptedProcs, curRun);
                curRun = &procCopy[nextProc++];
                timeChart[curTime] = curRun->id;
            } else {
                addProc(&pq, &procCopy[nextProc++]); 
            }
        }
        if(curRun == NULL) {
            if((temp = pop(&preemptedProcs)) != NULL) {
                curRun = temp;
                temp = NULL;
            } else if((curRun = getNextProc(&pq)) == NULL) {
                // no more procs to run
                break;
            } 
            timeChart[curTime] = curRun->id;
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
        curTime++;
    }

    printResults(finished, finishedIndex, timeChart, iters, numProcs, curTime);
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    cleanupQueue(&preemptedProcs);
    preemptedProcs = NULL;
    free(finished);
    finished = NULL;
	cleanupPriorityQueue(&pq);
	pq = NULL;
	free(procCopy);
	procCopy = NULL;
}
