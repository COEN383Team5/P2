#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "AlgObject.h"

AlgObject *createAlgObject(ProcInfo *procs, int numProcs) {
    AlgObject *a = (AlgObject *)malloc(sizeof(AlgObject));
    a->unstarted = (ProcInfo *)malloc(numProcs*sizeof(ProcInfo));
    memcpy(a->unstarted, procs, numProcs*sizeof(ProcInfo));
    a->started = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    a->finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    // 10240 = 10*2^10 and is completely arbitrary
    a->timeChart = (int *)calloc(10240, sizeof(int));
    a->unstartedIndex = 0; 
    a->startedIndex = 0;
    a->finishedIndex = 0;
    a->timeChartIndex = 0;
    a->numProcs = numProcs;
    return a;
}

cleanupAlgObject(AlgObject *a) {
    free(a->unstarted);
    free(a->started);
    free(a->finished);
    free(a->timeChart);
    free(a);
}

void first100NoPrempt(AlgObject *a) {
    int i;
    // do 100 quanta or give every process a turn, whichever is fewer quanta
    for(i = 0; i < 100 && a->unstartedIndex+1 < a->numProcs; i++) {
        a->timeChart[a->timeChartIndex++] = a->unstarted[a->unstartedIndex].id; 
        a->unstarted[a->unstartedIndex].completedRunTime++;
        a->unstarted[a->unstartedIndex].totalWaitTime += a->timeChartIndex-a->unstarted[a->unstartedIndex].lastRunTime;
        a->unstarted[a->unstartedIndex].lastRunTime = a->timeChartIndex;
        a->started[a->startedIndex++] = &(a->unstarted[a->unstartedIndex]);
        if(a->unstarted[a->unstartedIndex].totalRunTime <= a->unstarted[a->unstartedIndex].completedRunTime) {
            // unstarted[unstartedIndex] has completed all it will need to complete
            a->finished[a->finishedIndex++] = a->started[--a->startedIndex];
            a->started[a->startedIndex] = 0;
        }
        a->unstartedIndex++;
    }

}

void printResults(AlgObject *a) {
    int i;
    float waitTimeTemp, turnAroundTemp;
    printf("\nTime chart:\n");
    for(i = 0; i < a->timeChartIndex; i++) {
        printf("%d ", a->timeChart[i]);
    }   
    printf("\n\n");
    printf("Stats for procs:\n");
    for(i = 0; i < a->finishedIndex; i++) {
       waitTimeTemp = ((float)a->finished[i]->totalWaitTime)/ceil(a->finished[i]->totalRunTime);
       turnAroundTemp = a->finished[i]->totalWaitTime+a->finished[i]->completedRunTime;

       printf("Proc id: %3d,\tAverage turnaround time: %.4f,\tAverage waiting time: %.4f\tAverage response time %.4f\n", a->finished[i]->id, turnAroundTemp, waitTimeTemp, waitTimeTemp); 
    }
}

void giveQuanta(AlgObject *a, int i) {

}
