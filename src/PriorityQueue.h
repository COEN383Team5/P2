#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Node.h"

typedef struct PriorityQueue {
	Queue **queues;
	int numPriorities;
} PriorityQueue;

/* creates a PriorityQueue with numPriorities priorities
 * @param numPriorities
 *		the number of priorities to support
 * @retval a heap allocated PriorityQueue with no data in it
 */
PriorityQueue *initializePriorityQueue(int numPriorities);

/* Frees the memory in pq 
 * @param pq
 *		a reference to a PriorityQueue created by initializePriorityQueue
 */
void cleanupPriorityQueue(PriorityQueue **pq);

/* Fills pq with the procs based on the procs priority
 * @param pq
 *		the priority queue to be filled
 * @param procs
 * 		the processes to be put into priority queues
 * 		they should already be sorted by arrival time
 * @param numProcs
 *		the number of ProcInfos in procs
 */
void fillPriorityQueue(PriorityQueue **pq, ProcInfo *procs, int numProcs);

/* Returns the highest priority process, if there is on
 * @param pq
 *		a reference to a PriorityQueue
 * @retval the highest priority process, or NULL if there are no more processes
 * 		it is the programmer's responsiblity to free retval
 */
ProcInfo *getNextProc(PriorityQueue **pq);

/* adds proc into the appropriate Queue in the PriorityQueue
 * @param pq
 * 		a reference to a PriorityQueue
 * @param proc
 * 		a reference to a ProcInfo to add to the PriorityQueue
 */
void addProc(PriorityQueue **pq, ProcInfo *proc);

#endif