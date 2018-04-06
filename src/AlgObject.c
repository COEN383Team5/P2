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
    a->timeSinceStart = 0;
    a->numProcs = numProcs;
    return a;
}

void cleanupAlgObject(AlgObject *a) {
    free(a->unstarted);
    free(a->started);
    free(a->finished);
    free(a->timeChart);
    free(a);
}

void first100(AlgObject *a, int preemptive) {
    int i;
    float timeLeftForProc;
    // do 100 quanta or give every process a turn, whichever is fewer quanta
    for(i = 0; i < 100 && a->unstartedIndex+1 < a->numProcs; i++) {
        a->timeChart[a->timeChartIndex++] = a->unstarted[a->unstartedIndex].id; 
        timeLeftForProc = a->unstarted[a->unstartedIndex].totalWaitTime-a->unstarted[a->unstartedIndex].completedRunTime;
        if(timeLeftForProc < 1 && preemptive) {
            a->unstarted[a->unstartedIndex].completedRunTime += timeLeftForProc;
            a->timeSinceStart += timeLeftForProc;
        } else {
            a->unstarted[a->unstartedIndex].completedRunTime += 1;
            a->timeSinceStart += 1;
        }
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

void first100NonPreemptive(AlgObject *a) {
    first100(a, 0);
}

void first100Preemptive(AlgObject *a) {
    first100(a, 1);
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
    printf("Throughput: %.4f processes/quanta\n", a->numProcs/a->timeSinceStart);
}

void giveQuanta(AlgObject *a, int i, int preemptive) {
    float timeLeftForProc;
	a->timeChart[a->timeChartIndex++] = a->started[i]->id;
    timeLeftForProc = a->started[i]->totalRunTime-a->started[i]->completedRunTime;
    if(timeLeftForProc < 1 && preemptive) {
        a->started[i]->completedRunTime += timeLeftForProc;
        a->timeSinceStart += timeLeftForProc;
    } else {
        a->started[i]->completedRunTime += 1;
        a->timeSinceStart += 1;
    }
	a->started[i]->totalWaitTime += a->timeSinceStart-a->started[i]->lastRunTime;
	a->started[i]->lastRunTime = a->timeSinceStart;
	if(a->started[i]->totalRunTime <= a->started[i]->completedRunTime) {
		// this process has finished so remove it from started
		// without messing up the order of started
		a->finished[a->finishedIndex++] = a->started[i];
		if(i+1 < a->startedIndex) {
			memmove(&a->started[i], &a->started[i+1],(a->startedIndex-(i+1))*sizeof(ProcInfo *));
		}   
		a->started[--a->startedIndex] = 0;
	}
}

void giveQuantaNonPremptive(AlgObject *a, int i) {
    giveQuanta(a, i, 0);
}

void giveQuantaPremptive(AlgObject *a, int i) {
    giveQuanta(a, i, 1);
}
