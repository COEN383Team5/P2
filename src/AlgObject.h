#ifndef ALGOBJECT_H
#define ALGOBJECT_H

#include "ProcInfo.h"

// stores the necessary data to keep track of the processes as they get quanta
typedef struct AlgObject {
    ProcInfo *unstarted, **started, **finished;
    // timeChart stores in order which processes were allowed to run
    int *timeChart;
    int unstartedIndex, startedIndex, finishedIndex, timeChartIndex, numProcs;
    float timeSinceStart;
} AlgObject;


/* Creates an AlgObject using procs. retval->unstarted is a copy of procs 
 * @param procs
 *      the processes that are to be given quanta
 * @param numProcs
 *      the number of processes in procs
 * @retval a heap allocated and initialized AlgObject
 */
AlgObject *createAlgObject(ProcInfo *procs, int numProcs); 

/* frees all the relavent memory in a
 * @param a
 *      a heap allocated AlgObject created by createAlgObject(2)
 */
void cleanupAlgObject(AlgObject *a);

/* distributes the first 100 quanta to the processes in a, unless there are not 100 processes
 * in which case it gives each process a turn, adds them to a->started, and the returns
 * @param a
 *      an AlgObject created by createAlgObject(2)
 */
void first100(AlgObject *a);

/* prints the a->timeChart and timing information for the procs in a
 * @param a
 *      an AlgObject created by createAlgObject(2)
 */
void printResults(AlgObject *a);

/* gives a->started[i] some portion of a quanta and updates the relavent variables
 * @param a
 *      an AlgObject created by createAlgObject(2)
 * @param i
 *      the index in a->started[i] for the proc that is going to get a quanta
 * @param preemptive
 *      a boolean that determines whether to preemptively schedule or not
 */
void giveQuanta(AlgObject *a, int i, int preemptive);

/* gives a->started[i] a quanta nonpreemtively and updates the relavent variables
 * calls giveQuanta(3)
 * @param a
 *      an AlgObject created by createAlgObject(2)
 * @param i
 *      the index in a->started[i] for the proc that is going to get a quanta
 */
void giveQuantaNonPremptive(AlgObject *a, int i);

/* gives a->started[i] a quanta preemtively and updates the relavent variables
 * calls giveQuanta(3)
 * @param a
 *      an AlgObject created by createAlgObject(2)
 * @param i
 *      the index in a->started[i] for the proc that is going to get a quanta
 */
void giveQuantaPremptive(AlgObject *a, int i);

#endif
