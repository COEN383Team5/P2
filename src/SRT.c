#include <stdio.h>
#include <float.h>
#include "SRT.h"

int getProcWithShortestRemainingTime(AlgObject *a) {
    int i, shortest = 0;
    float temp /*= a->started[0]->totalRunTime-a->started[0]->completedRunTime*/;
    float shortestVal = FLT_MAX;
    for(i = 0; i < a->startedIndex; i++) {
        if (a->started[i] == NULL) {
            continue;
        }
        temp = a->started[i]->totalRunTime-a->started[i]->completedRunTime;
        if(shortestVal > temp) {
            shortestVal = temp;
            shortest = i;
        }
    }
    return shortest;
}

void doSRT(ProcInfo *procs, int numProcs) {
    // sjp = index to shortestJobProcess in a->started
    int sjp, curTime = 0, nextProc = 0;
    AlgObject *a = createAlgObject(procs, numProcs);
    ProcInfo *curRun = NULL;

    printf("Starting shortest remaining time algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    while(1) {
        // schedule processes
        if(curTime < desiredQuanta && nextProc < numProcs && a->unstarted[nextProc].arrivalTime <= curTime) {
            if(curRun != NULL 
                    && a->unstarted[nextProc].totalRunTime < curRun->totalRunTime - curRun->completedRunTime
            ) {
                // preempt
                // curRun->timesWaited++;
                printf("%d was preempted by %d\n", curRun->id, a->unstarted[nextProc].id);
                curRun = &(a->unstarted[nextProc++]);
                // a->timeChart[a->timeChartIndex++] = curRun->id; // does this line make it run for 2 quanta?
                a->started[a->startedIndex++] = curRun;
            } else {
               a->started[a->startedIndex++] = &(a->unstarted[nextProc++]);
            }
        }

        // run processes
        if (curRun == NULL) {
            sjp = getProcWithShortestRemainingTime(a);
            if (a->started[sjp] != NULL) {
                curRun = a->started[sjp];
            } else if (a->finishedIndex == numProcs && curTime > desiredQuanta) {
                break;
            }
        }

        if (curRun != NULL) {
            a->timeChart[a->timeChartIndex++] = curRun->id;
            giveQuantaToProc(curRun, curTime);
            if(curRun->completedRunTime > curRun->totalRunTime) {
                a->started[a->startedIndex--] = NULL;
                printf("proc: %d; finishedIndex: %d\n", curRun->id, a->finishedIndex);
                a->finished[a->finishedIndex++] = curRun;
                curRun = NULL;
            }
        }

        curTime++;
    }

    printResults(a->finished, a->finishedIndex, a->timeChart, a->timeChartIndex, a->numProcs, a->timeSinceStart);
    // cleanupAlgObject(&a);
}
