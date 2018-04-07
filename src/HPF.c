#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HPF.h"

RunInfo *first100HPF(ProcInfo **procs, int numProcs, int preemptive) {
	RunInfo *retval = (RunInfo *)calloc(1, sizeof(RunInfo));
	retval->timeChart = (int *)calloc(10240, sizeof(int));
	for(retval->iters = 0; retval->iters < 100 && retval->iters < numProcs; retval->iters++) {
		retval->timeChart[retval->iters] = (*procs)[retval->iters].id;
		if((*procs)[retval->iters].totalRunTime < 1 && preemptive) {
			(*procs)[retval->iters].totalWaitTime += retval->runTime-(*procs)[retval->iters].lastRunTime;
			retval->runTime += (*procs)[retval->iters].totalRunTime;
			(*procs)[retval->iters].lastRunTime = retval->runTime;
			(*procs)[retval->iters].completedRunTime = (*procs)[retval->iters].totalRunTime;
		} else {
			(*procs)[retval->iters].totalWaitTime += retval->runTime-(*procs)[retval->iters].lastRunTime;
			retval->runTime += 1;
			(*procs)[retval->iters].lastRunTime = retval->runTime;
			(*procs)[retval->iters].completedRunTime += 1;
		}
	}
	return retval;
}

void doHPF(ProcInfo *procs, int numProcs, int preemptive) {
	RunInfo *ri;
	float timeLeft, waitTimeTemp, turnAroundTemp;
	ProcInfo *temp, *procCopy = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
	ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
	int i, finishedIndex = 0;
	PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

	memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));

	printf("Starting highest priority first algorithm");
    if(preemptive) {
        printf(" with preemption\n\n");
    } else {
        printf(" without preemption\n\n");
    }
	printProcs(procs, numProcs, stdout);

	ri = first100HPF(&procCopy, numProcs, preemptive);
	fillPriorityQueue(&pq, procCopy, numProcs);


	while((temp = getNextProc(&pq)) != NULL) {
		ri->timeChart[ri->iters] = temp->id;
		timeLeft = temp->totalRunTime-temp->completedRunTime;
		if(timeLeft < 1 && preemptive) {
			temp->totalWaitTime += ri->runTime-temp->lastRunTime;
			ri->runTime += timeLeft;
			temp->lastRunTime = ri->runTime;
			temp->completedRunTime += timeLeft;
		} else {
			temp->totalWaitTime += ri->runTime-temp->lastRunTime;
			ri->runTime += 1;
			temp->lastRunTime = ri->runTime;
			temp->completedRunTime += 1;
		}
		if(temp->completedRunTime < temp->totalRunTime) {
			addProc(&pq, temp);
		} else {
			finished[finishedIndex++] = temp; 
		}
		ri->iters++;
	}

    printResults(finished, finishedIndex, ri->timeChart, ri->iters, numProcs, ri->runTime);
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    free(finished);
	cleanupPriorityQueue(&pq);
	pq = NULL;
	free(procCopy);
	procCopy = NULL;
}
