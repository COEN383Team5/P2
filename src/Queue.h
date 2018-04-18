#ifndef QUEUE_H
#define QUEUE_H

#include "ProcInfo.h"

// A node for a doubly linked list
typedef struct Node {
	ProcInfo *proc;
	struct Node *next, *prev;
} Node;

// Doubly linked list
typedef struct Queue {
	Node *head, *tail;
} Queue;

/* Creates an empty doubly linked list
 * @retval a Queue allocated on the heap with a dummy node
 */
Queue *initializeQueue();

/* Frees the memory of a Queue 
 * @param a
 * 		a Queue that was initialized with initializeQueue()
 */
void cleanupQueue(Queue **a);

/* Adds proc to the end of a
 * @param Queue
 * 		the queue to add proc to the end of
 * @param proc
 * 		a pointer to the proc to add to the queue
 */
void addToQueue(Queue *a, ProcInfo *proc);

/* returns the element at the head of the queue, if there is one
 * @param a
 * 		a reference to the queue to retreive the data from
 *      the data will no longer be in the queue when this function returns
 * @retval a reference to the data that was stored at the head of the queue
 * 		if there is no valid data in the queue, retval will be NULL
 *		it is up to the programmer to ensure that this return value is freed when it is no longer needed
 *		otherwise there will be a memory leak
 */
ProcInfo *pop(Queue *a);

/* Convience function that prints the contents of the queue
 * @param a
 *      the queue to print the contents of
 * @param stream
 *      the stream to print to
 */
void printQueue(Queue *a, FILE *stream);

#endif
