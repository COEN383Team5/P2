#ifndef HPF_H
#define HPF_h

#include "ProcInfo.h"
#include "AlgObject.h"
#include "PriorityQueue.h"

typedef struct RunInfo {
    int *timeChart;
    double runTime;
    int iters;
} RunInfo;

RunInfo *first100HPF(ProcInfo **procs, int numProcs, int preemptive);

void doHPF(ProcInfo *procs, int numProcs, int preemptive);

#endif
