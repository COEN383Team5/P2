#ifndef SJF_H
#define SJF_h

#include "ProcInfo.h"
#include "AlgObject.h"

int getProcWithShortestJob(AlgObject *a);

void doSJF(ProcInfo *procs, int numProcs);

#endif
