#ifndef ALGOBJECT_H
#define ALGOBJECT_H

#include "ProcInfo.h"

// stores the necessary data to keep track of the processes as they get quanta
typedef struct AlgObject {
    ProcInfo *unstarted, **started, **finished;
    // timeChart stores in order which processes were allowed to run
    int *timeChart;
    int unstartedIndex, startedIndex, finishedIndex, timeChartIndex, numProcs;
    double timeSinceStart;
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
 *      a reference to a heap allocated AlgObject created by createAlgObject(2)
 */
void cleanupAlgObject(AlgObject **a);

#endif
