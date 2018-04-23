#include <math.h>
#include <stdio.h>
#include "SJF.h"


void giveQuantaToProc(ProcInfo *proc, int curTime);

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

void doSJF(ProcInfo *procs, int numProcs) {
    // sjp = index to shortestJobProcess in a->started
    //int sjp;
    AlgObject *a = createAlgObject(procs, numProcs);

    int curTime = 0, nextUnstartedProc = 0;
    //ProcInfo *curRun = NULL;

    printf("Starting shortest job first algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    for (int i = 0; i < numProcs; i++) {
        
        // update the list of arrived processes
        while (a->unstarted[nextUnstartedProc].arrivalTime <= curTime) {
            a->started[a->startedIndex++] = &(a->unstarted[nextUnstartedProc++]);
        }

        // choose the shortest job from the arrived processes and run it
        ProcInfo *curRun = a->started[getProcWithShortestJob(a)];
        int newTime = curTime + ceil(curRun->totalRunTime);
        for (int j = curTime; j < newTime; j++) {
            a->timeChart[a->timeChartIndex++] = curRun->id;
        }
        curTime = newTime;

    }
    
    // while (1) {

    //     // check if any new processes have arrived
    //     if (curTime < desiredQuanta && nextProc < numProcs && a->unstarted[nextProc].arrivalTime <= curTime) {
    //         a->started[a->startedIndex++] = &(a->unstarted[nextProc++]);
    //     }

    //     // if no process is currently running, pick a new one
    //     if (curRun == NULL) {
    //         sjp = getProcWithShortestJob(a);
    //         if (a->started[sjp] != NULL) {
    //             curRun = a->started[sjp];
    //         } else if (a->finishedIndex == numProcs && curTime > desiredQuanta) {
    //             break;
    //         }
    //     }

    //     if (curRun != NULL) {
    //         a->timeChart[a->timeChartIndex++] = curRun->id;
    //         giveQuantaToProc(curRun, curTime);

    //         // if the current process has been completed,
    //         // remove it from the started queue and add
    //         // it to the finished queue
    //         if (curRun->completedRunTime > curRun->totalRunTime) {
    //             a->started[a->startedIndex--] = NULL;
    //             a->finished[a->finishedIndex++] = curRun;
    //             curRun = NULL;
    //             printf("proc: %d; finishedIndex: %d\n", curRun->id, a->finishedIndex);
    //         }
    //     }

    // }

    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    cleanupAlgObject(&a);
}
