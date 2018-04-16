#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HPF.h"

void doHPF(ProcInfo *procs, int numProcs, int preemptive) {
	RunInfo *ri;
	float timeLeft;
	ProcInfo *temp, *procCopy = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
	ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
	int finishedIndex = 0;
	PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

	memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));

	printf("Starting highest priority first algorithm");
    if(preemptive) {
        printf(" with preemption\n\n");
    } else {
        printf(" without preemption\n\n");
    }
	printProcs(procs, numProcs, stdout);

// TODO have to get first 100 before filling priority queue
//	ri = first100HPF(&procCopy, numProcs, preemptive);
	fillPriorityQueue(&pq, procCopy, numProcs);


	while((temp = getNextProc(&pq)) != NULL) {
   // TODO 
	}

    printResults(finished, finishedIndex, ri->timeChart, ri->iters, numProcs, ri->runTime);
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    free(finished);
	cleanupPriorityQueue(&pq);
	pq = NULL;
	free(procCopy);
	procCopy = NULL;
}
