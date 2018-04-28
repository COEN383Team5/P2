#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "SJF.h"

/**
 * Given an AlgObject, traverses its queue of started processes and finds the
 * one with the shortest total run time.
 * Returns: the index of the shortest job, or -1 if there are no jobs.
 */
int getShortestJobIndex(AlgObject *a) {
    int result = 0;

    // find the first non-null entry to return as a default
    while (a->started[result] == NULL) {
        result++;
        if (result >= a->startedIndex) {
            return -1;
        }
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

/**
 * Performs a simulation of the Shortest Job First scheduling algorithm given a
 * list of processes and relevant information (e.g. arrival time, total run
 * time, etc.).  Performance metrics are printed to stdout.
 */
void doSJF(ProcInfo *procs, int numProcs) {

    AlgObject *a = createAlgObject(procs, numProcs);

    int curTime = 0;            // the current time, measured in quanta
    int nextUnstartedProc = 0;  // the index into the queue of processes

    printf("Starting shortest job first algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    for (int i = 0; i < numProcs; i++) {
        
        // update the list of arrived processes
        while (nextUnstartedProc < numProcs && a->unstarted[nextUnstartedProc].arrivalTime <= curTime) {
            a->started[a->startedIndex++] = &(a->unstarted[nextUnstartedProc++]);
        }

        // choose the shortest job from the arrived processes
        int curRunIndex = getShortestJobIndex(a);

        // if getShortestJobIndex returns -1, no new procs have arrived
        if (curRunIndex == -1) {
            curTime++;
            continue;
        }

        // if a job was found, run it
        ProcInfo *curRun = a->started[curRunIndex];
        int newTime = curTime + ceil(curRun->totalRunTime);
        for (int j = curTime; j < newTime; j++) {
            a->timeChart[a->timeChartIndex++] = curRun->id;
        }

        // set the statistics for the process
        curRun->completedRunTime = newTime - curTime;
        curRun->startTime = curTime;
        curRun->responseTime = curTime - curRun->arrivalTime;
        curRun->totalWaitTime = curRun->responseTime;
        curRun->timesWaited = 1;    // what is this?
        curRun->lastRunTime = curTime;

        a->timeSinceStart = curTime + curRun->totalRunTime;
        curTime = newTime;

        // move the process that just ran from the started to the finished queue
        a->finished[a->finishedIndex++] = curRun;
        a->started[curRunIndex] = NULL;

        // don't schedule any jobs after desiredQuanta has elapsed
        if (curTime > desiredQuanta) {
            break;
        }

    }

    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
