#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProcInfo.h"


// TODO add timing stuff by making started and finished a struct that has the timing info
void doFCFS(ProcInfo *procs, int numProcs) {
    // timeChart stores in order which processes were allowed to run
    // 10240 = 10*2^10 and is completely arbitrary
    int i, timeChart[10240];
    ProcInfo *unstarted = procs;
    ProcInfo **started = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    int unstartedIndex = 0, startedIndex = 0, finishedIndex = 0, timeChartIndex = 0;

    printf("Starting first come first serve algorithm\n\n");
    printProcs(procs, numProcs, stdout);
    
    // inital 100 quanta
    for(i = 0; i < 100; i++) {
        if(startedIndex+1 < numProcs && unstartedIndex+1 < numProcs) {
            timeChart[timeChartIndex++] = unstarted[unstartedIndex].id; 
            started[startedIndex++] = &unstarted[unstartedIndex];
            unstarted[unstartedIndex].completedRunTime++;
            if(unstarted[unstartedIndex].totalRunTime <= unstarted[unstartedIndex].completedRunTime) {
                // unstarted[unstartedIndex] has completed all it will need to complete
                finished[finishedIndex++] = started[startedIndex];
                started[--startedIndex] = 0;
            }
            unstartedIndex++;
        } else {
            // all processes got a turn
            break;
        }
    }

    while(startedIndex > 0) {
        // there are some processes that need to finish executing
        for(i = 0; i < startedIndex; i++) {
            timeChart[timeChartIndex++] = started[i]->id;
            started[i]->completedRunTime++;
            if(started[i]->totalRunTime <= started[i]->completedRunTime) {
                // this process has finished so remove it from started
                // without messing up the order of started
                if(i+1 < startedIndex) {
                    memmove(&started[i], &started[i+1],startedIndex-(i+1));
                }
                finished[finishedIndex++] = started[startedIndex];
                started[--startedIndex] = 0;
            }
        }
    }
    printf("Time chart: ");
    for(i = 0; i < timeChartIndex; i++) {
        printf("%d ", timeChart[i]);
    }
    printf("\n");
}
