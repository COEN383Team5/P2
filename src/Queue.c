#include <stdlib.h>
#include "Queue.h"

Queue *initializeQueue() {
	Queue *retval = (Queue *)malloc(sizeof(Queue));
    retval->tail = (Node *)calloc(1,sizeof(Node));
    retval->head = retval->tail;
	return retval;
}

void cleanupQueue(Queue *a) {
	ProcInfo *temp;
	if(a != NULL) {
		while((temp = pop(a)) != NULL) {
        /*  This may cause a double free if the ProcInfo is later freed again 
         *  or may cause free to throw an exception if the ProcInfo is in the
         *  middle of section of the heap allocated to an array of ProcInfos
         *  which is the case most of the time
         *
         *  Since the code in this repo only cleans up the queue when it is empty
         *  this is not a concern, but if this code is used else where then this 
         *  may prevent a memory leak, or inform the user of what is going on.
         */
			free(temp); 
			temp = NULL;
		}
		free(a);
		a = NULL;
	}
}

void addToQueue(Queue *a, ProcInfo *proc) {
	a->tail->next = (Node *)calloc(1,sizeof(Node));
	a->tail->next->prev = a->tail;
	a->tail = a->tail->next;
	a->tail->proc = proc;
}

ProcInfo *pop(Queue *a) {
	Node *temp;
	ProcInfo *retval = NULL;
	if(a->head->next != NULL && a->head->next->proc != NULL){
		retval = a->head->next->proc;
		temp = a->head->next;
        if(temp == a->tail) {
            a->tail = a->head;    
        }
		a->head->next = a->head->next->next;	
		free(temp);
		temp = NULL;
	}
	return retval;
}

void printQueue(Queue *a, FILE *stream) {
    Node *temp = a->head->next;
    while(temp != NULL && temp->proc != NULL) {
        fprintf(stream, "%d ", temp->proc->id);
        temp = temp->next;
    }
}
