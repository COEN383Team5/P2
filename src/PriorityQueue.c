#include <stdlib.h>
#include "PriorityQueue.h"

PriorityQueue *initializePriorityQueue(int numPriorities) {
	int i;
	PriorityQueue *retval = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	retval->numPriorities = numPriorities;
	retval->queues = (Queue **)calloc(numPriorities, sizeof(Queue *));
	for(i = 0; i < numPriorities; i++) {
		retval->queues[i] = initializeQueue();
	}
	return retval;
}

void cleanupPriorityQueue(PriorityQueue **pq) {
	int i;
	if(*pq != NULL) {
		for(i = 0; i < (*pq)->numPriorities; i++) {
			cleanupQueue(&((*pq)->queues[i]));
		}
		free((*pq)->queues);
		(*pq)->queues = NULL;
		free(*pq);
		*pq = NULL;
	}
}

void fillPriorityQueue(PriorityQueue **pq, ProcInfo *procs, int numProcs) {
	int i;
	for(i = 0; i < numProcs; i++) {
		addToQueue(&((*pq)->queues[procs[i].priority-1]), &procs[i]); 
	}
}

ProcInfo *getNextProc(PriorityQueue **pq) {
	int i;
	ProcInfo *temp = NULL;
	for(i = 0; i < (*pq)->numPriorities; i++) {
		if((temp = pop(&((*pq)->queues[i]))) != NULL) {
			break; // found a valid ProcInfo
		}
	}
	return temp;
}

void addProc(PriorityQueue **pq, ProcInfo *proc) {
	addToQueue(&((*pq)->queues[proc->priority-1]), proc);
}

void printPQ(PriorityQueue *pq) {
    int i;
    for(i = 0; i < pq->numPriorities; i++) {
        printf("Priority %d: ", i+1);
        printQueue(pq->queues[i]);
        printf("\n");
    }
    printf("\n");
}
