#include "PriorityQueue.h"

PriorityQueue *initializePriorityQueue(int numPriorities) {
	int i;
	PriorityQueue *retval = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	retval->numPriorities = numPriorities;
	retval->queues = (DLL **)calloc(numPriorities, sizeof(DLL *));
	for(i = 0; i < numPriorities; i++) {
		retval->queues[i] = initializeDLL();
	}
	return retval;
}

void cleanupPriorityQueue(PriorityQueue **pq) {
	int i;
	if(*pq != NULL) {
		for(i = 0; i < (*pq)->numPriorities; i++) {
			cleanupDLL((*pq)->queues[i]);
		}
		free((*pq)->queues)
		(*pq)->queues = NULL;
		free(*pq);
		*pq = NULL;
	}
}

void fillPriorityQueue(PriorityQueue **pq, ProcInfo *procs, int numProcs) {
	int i;
	for(i = 0; i < numProcs; i++) {
		addToQueue(&((*pq)->queues[procs[i].priority]), &procs[i]); 
	}
}

ProcInfo *getNextProc(PrioirtyQueue **pq) {
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
	addToQueue(&((*pq)->queues[proc->priority]), proc);
}