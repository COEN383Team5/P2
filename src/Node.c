#include <stdlib.h>
#include "Node.h"

Queue *initializeQueue() {
	Queue *retval = (Queue *)malloc(sizeof(Queue));
	retval->head = retval->tail = (Node *)calloc(1,sizeof(Node));
	return retval;
}

void cleanupQueue(Queue **a) {
	ProcInfo *temp;
	if(a != NULL) {
		while((temp = pop(a)) != NULL) {
			free(temp); // This may cause a double free if the ProcInfo is later freed again 
			temp = NULL;
		}
		free(*a);
		*a = NULL;
	}
}

void addToQueue(Queue **a, ProcInfo *proc) {
	(*a)->tail->next = (Node *)calloc(1,sizeof(Node));
	(*a)->tail->next->prev = (*a)->tail;
	(*a)->tail = (*a)->tail->next;
	(*a)->tail->proc = proc;
}

ProcInfo *pop(Queue **a) {
	Node *temp;
	ProcInfo *retval = NULL;
	if((*a)->head->proc != NULL){
		retval = (*a)->head->proc;
		temp = (*a)->head;
		(*a)->head = (*a)->head->next;	
		free(temp);
		temp = NULL;
	}
	return retval;
}
