#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AlgObject.h"

AlgObject *createAlgObject(ProcInfo *procs, int numProcs) {
    AlgObject *a = (AlgObject *)malloc(sizeof(AlgObject));
    a->unstarted = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
    memcpy(a->unstarted, procs, numProcs*sizeof(ProcInfo));
    a->started = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    a->finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    // 10240 = 10*2^10 and is completely arbitrary
    a->timeChart = (int *)calloc(10240, sizeof(int));
    a->unstartedIndex = 0; 
    a->startedIndex = 0;
    a->finishedIndex = 0;
    a->timeChartIndex = 0;
    a->timeSinceStart = 0;
    a->numProcs = numProcs;
    return a;
}

void cleanupAlgObject(AlgObject **a) {
    if(*a != NULL) {
        free((*a)->unstarted);
        (*a)->unstarted = NULL;
        free((*a)->started);
        (*a)->started = NULL;
        free((*a)->finished);
        (*a)->finished = NULL;
        free((*a)->timeChart);
        (*a)->timeChart = NULL;
        free(*a);
        *a = NULL;
    }
}
