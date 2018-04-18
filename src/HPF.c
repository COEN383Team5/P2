#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HPF.h"
#include "Stack.h"

void giveQuantaToProc(ProcInfo *proc, int curTime) {
    if(proc->completedRunTime == 0) {
        proc->totalWaitTime += curTime-proc->arrivalTime;
        proc->startTime = curTime;
        proc->responseTime = proc->totalWaitTime;
    }
    proc->completedRunTime++;
}

void doHPF(ProcInfo *procs, int numProcs, int preemptive) {
    Stack *preemptedProcs;
    int timeChart[10240];
	ProcInfo *temp, *curRun = NULL, *procCopy = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
	ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
	int finishedIndex = 0, nextProc = 0, curTime = 0, chartIndex = 0;
	PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

	memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));
    preemptedProcs = createStack();

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
                addToStack(&preemptedProcs, curRun);
                printf("%d was preempted by %d\n", curRun->id, procCopy[nextProc].id);
                curRun = &procCopy[nextProc++];
                timeChart[chartIndex++] = curRun->id;
            } else {
                addProc(&pq, &procCopy[nextProc++]); 
            }
        }
        if(curRun == NULL) {
            if((temp = popStack(&preemptedProcs)) != NULL) {
                printf("Running proc that was preempted %d\n", temp->id);
                curRun = temp;
                temp = NULL;
            } else if((curRun = getNextProc(&pq)) == NULL && curTime > desiredQuanta) {
                // no more procs to run
                break;
            } 
            if(curRun != NULL) {
                timeChart[chartIndex++] = curRun->id;
            } else {
                fprintf(stderr, "Processor was unused during %d quantum\n", curTime);
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
        curTime++;
    }

    printResults(finished, finishedIndex, timeChart, chartIndex, numProcs, curTime);
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    freeStack(&preemptedProcs);
    preemptedProcs = NULL;
    free(finished);
    finished = NULL;
	cleanupPriorityQueue(&pq);
	pq = NULL;
	free(procCopy);
	procCopy = NULL;
}
