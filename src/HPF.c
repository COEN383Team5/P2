#include "HPF.h"

typedef struct RunInfo {
	int *timeChart;
	float runTime;
	int iters;
} RunInfo;

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
	RunInfo ri;
	float timeLeft, waitTimeTemp, turnAroundTemp;
	ProcInfo *temp, *procCopy = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
	ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
	int finishedIndex = 0;
	PriorityQueue *pq = initializePriorityQueue(NUM_PRIORITIES);	

	memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));

	printf("Starting highest priority first algorithm\n\n");
	printProcs(proc, numProcs, stdout);

	ri = first100HPF(&procCopy, numProcs, preemptive);
	fillPriorityQueue(&pq, procCopy, numProcs);


	while((temp = getNextProc(&pq)) != NULL) {
		ri->timeChart[ri->iters] = temp->id;
		timeLeft = temp->totalRunTime-temp->completedRunTime;
		if(timeLeft < 1 && preemptive) {
			temp->totalWaitTime += ri->runTime-temp->lastRunTime;
			ri->runTime += timeLeft;
			ri->lastRunTime = ri->runTime;
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
			finshed[finishedIndex++] = temp; 
		}
		ri->iters++;
	}

    printf("\nTime chart:\n");
    for(i = 0; i < ri->iters; i++) {
        printf("%d ", ri->timeChart[i]);
    }   
    printf("\n\n");
    printf("Stats for procs:\n");
    for(i = 0; i < finishedIndex; i++) {
       waitTimeTemp = ((float)finished[i]->totalWaitTime)/ceil(finished[i]->totalRunTime);
       turnAroundTemp = finished[i]->totalWaitTime+finished[i]->completedRunTime;

       printf("Proc id: %3d,\tAverage turnaround time: %.4f,\tAverage waiting time: %.4f\tAverage response time %.4f\n", finished[i]->id, turnAroundTemp, waitTimeTemp, waitTimeTemp); 
       free(finished[i]);
       finished[i] = NULL;
    }
    printf("Throughput: %.4f processes/quanta\n", numProcs/ri->runTime);

    free(finished);
	cleanupPriorityQueue(&pq);
	pq = NULL;
	free(procCopy); // may cause double free
	procCopy = NULL;
}