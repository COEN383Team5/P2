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
	if((*a)->head->next != NULL && (*a)->head->next->proc != NULL){
		retval = (*a)->head->next->proc;
		temp = (*a)->head->next;
		(*a)->head->next = (*a)->head->next->next;	
		free(temp);
		temp = NULL;
	}
	return retval;
}

void printQueue(Queue *a) {
    Node *temp = a->head->next;
    while(temp != NULL && temp->proc != NULL) {
        printf("%d ", temp->proc->id);
        temp = temp->next;
    }
}
