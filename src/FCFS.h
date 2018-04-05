#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ProcInfo.h"

void doFCFS(ProcInfo *procs, int numProcs) {
    // timeChart stores in order which processes were allowed to run
    // 10240 = 10*2^10 and is completely arbitrary
    int i, timeChart[10240];
    float waitTimeTemp;
    ProcInfo *unstarted = procs;
    ProcInfo **started = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    int unstartedIndex = 0, startedIndex = 0, finishedIndex = 0, timeChartIndex = 0;

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    for(i = 0; i < 100; i++) {
        if(startedIndex+1 < numProcs && unstartedIndex+1 < numProcs) {
            timeChart[timeChartIndex++] = unstarted[unstartedIndex].id; 
            unstarted[unstartedIndex].completedRunTime++;
            unstarted[unstartedIndex].totalWaitTime += timeChartIndex-unstarted[unstartedIndex].lastRunTime;
            unstarted[unstartedIndex].lastRunTime = timeChartIndex;
            started[startedIndex++] = &unstarted[unstartedIndex];
            if(unstarted[unstartedIndex].totalRunTime <= unstarted[unstartedIndex].completedRunTime) {
                // unstarted[unstartedIndex] has completed all it will need to complete
                finished[finishedIndex++] = started[--startedIndex];
                started[startedIndex] = 0;
            }
            unstartedIndex++;
        } else {
            // all processes got a turn
            break;
        }
    }
    
    // inital 100 quanta

    while(startedIndex > 0) {
        // there are some processes that need to finish executing
        for(i = 0; i < startedIndex; i++) {
            timeChart[timeChartIndex++] = started[i]->id;
            started[i]->completedRunTime++;
            started[i]->totalWaitTime += timeChartIndex-started[i]->lastRunTime;
            started[i]->lastRunTime = timeChartIndex;
            if(started[i]->totalRunTime <= started[i]->completedRunTime) {
                // this process has finished so remove it from started
                // without messing up the order of started
                finished[finishedIndex++] = started[i];
                if(i+1 < startedIndex) {
                    memmove(&started[i], &started[i+1],startedIndex-(i+1));
                }
                started[--startedIndex] = 0;
            }
        }
    }
    printf("\nTime chart:\n");
    for(i = 0; i < timeChartIndex; i++) {
        printf("%d ", timeChart[i]);
    }
    printf("\n\n");
    printf("Stats for procs:\n");
    for(i = 0; i < finishedIndex; i++) {
       waitTimeTemp = ((float)finished[i]->totalWaitTime)/ceil(finished[i]->totalRunTime);
       printf("Proc id: %3d,\tAverage turnaround time: %4d,\tAverage waiting time: %.4f\tAverage response time %.4f\n", finished[i]->id, finished[i]->completedRunTime, waitTimeTemp, waitTimeTemp); 
    }
    free(started);
    free(finished);
}
