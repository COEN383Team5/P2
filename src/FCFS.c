#include <stdio.h>
#include <math.h>
#include "FCFS.h"
#include "AlgObject.h"

void doFCFS(ProcInfo *procs, int numProcs) {
    AlgObject *a = createAlgObject(procs, numProcs);
    int curTime = 0, nextUnstartedProc = 0;

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    //TODO
    for(int i = 0; i < numProcs; i++) { //run through all the processes
	// update the list of arrived processes
        while (nextUnstartedProc < numProcs && a->unstarted[nextUnstartedProc].arrivalTime <= curTime) {
            a->started[a->startedIndex++] = &(a->unstarted[nextUnstartedProc++]);
        }
    

    	//run jobs
        ProcInfo *curRun = a->started[i];
        int newTime = curTime + ceil(curRun->totalRunTime);
        for (int j = curTime; j < newTime; j++) {
            a->timeChart[a->timeChartIndex++] = curRun->id;
        }

	// set statistics for the process
        curRun->completedRunTime = newTime - curTime;
        curRun->startTime = curTime;
        curRun->responseTime = curTime - curRun->arrivalTime;
        curRun->totalWaitTime = curRun->responseTime;
        curRun->timesWaited = 1;    // ...
        curRun->lastRunTime = curTime;

	a->timeSinceStart = curTime + curRun->totalRunTime;
        curTime = newTime;

        // move the recently run process from started to finished queue
        a->finished[a->finishedIndex++] = curRun;
        a->started[i] = NULL;

        if (curTime > desiredQuanta) {
            break;
        }
    }


    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
