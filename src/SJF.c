#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "SJF.h"


int getProcWithShortestJob(AlgObject *a) {
    int i, shortest = 0;
    float temp = a->started[0]->totalRunTime;
    float shortestVal = temp;
    for(i = 1; i < a->startedIndex; i++) {
        temp = a->started[i]->totalRunTime;
        if(shortestVal > temp) {
            shortestVal = temp;
            shortest = i;
        }
    }
    return shortest;
}

int getShortestJobIndex(AlgObject *a) {
    int result = 0;

    // find the first non-null entry to return as a default
    while (a->started[result] == NULL) {
        result++;
        assert(result <= a->startedIndex);
    }

    // find an entry with a shorter job if it exists
    for (int i = result + 1; i < a->startedIndex; i++) {
        if (a->started[i] == NULL) {
            continue;
        }
        if (a->started[i]->totalRunTime < a->started[result]->totalRunTime) {
            result = i;
        }
    }

    return result;
}

void doSJF(ProcInfo *procs, int numProcs) {

    AlgObject *a = createAlgObject(procs, numProcs);

    int curTime = 0, nextUnstartedProc = 0;

    printf("Starting shortest job first algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    for (int i = 0; i < numProcs; i++) {
        
        // update the list of arrived processes
        while (nextUnstartedProc < numProcs && a->unstarted[nextUnstartedProc].arrivalTime <= curTime) {
            a->started[a->startedIndex++] = &(a->unstarted[nextUnstartedProc++]);
        }

        // choose the shortest job from the arrived processes and run it
        int curRunIndex = getShortestJobIndex(a);
        ProcInfo *curRun = a->started[curRunIndex];
        int newTime = curTime + ceil(curRun->totalRunTime);
        for (int j = curTime; j < newTime; j++) {
            a->timeChart[a->timeChartIndex++] = curRun->id;
        }

        // set the statistics for the process
        curRun->completedRunTime = newTime - curTime;
        curRun->startTime = curTime;
        curRun->responseTime = curTime - curRun->arrivalTime;
        curRun->totalWaitTime = 0;  // what is this?
        curRun->timesWaited = 0;    // what is this?
        curRun->lastRunTime = curTime;

        curTime = newTime;

        // move the process that just ran from the started to the finished queue
        a->finished[a->finishedIndex++] = curRun;
        a->started[curRunIndex] = NULL;

        if (curTime > desiredQuanta) {
            break;
        }

    }

    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
