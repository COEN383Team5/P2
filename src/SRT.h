#ifndef SRT_H
#define SRT_h

#include "ProcInfo.h"
#include "AlgObject.h"

int getProcWithShortestRemainingTime(AlgObject *a);

void doSRT(ProcInfo *procs, int numProcs);

#endif
