#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ProcInfo.h"

int partition(ProcInfo **procs, int low, int high) {
    int j, i = (low-1);
    ProcInfo temp;
    double pivotVal = (*procs)[high].arrivalTime;
    for(j = low; j < high; j++) {
        if((*procs)[j].arrivalTime <= pivotVal)  {
            i++;
            temp = (*procs)[j];
            (*procs)[j] = (*procs)[i];
            (*procs)[i] = temp;
        }
    }
    temp = (*procs)[i+1];
    (*procs)[i+1] = (*procs)[high];
    (*procs)[high] = temp;
    return i+1;
}

void quickSort(ProcInfo **procs, int low, int high) {
    if(low < high) {
        int pivot = partition(procs, low, high);
        quickSort(procs, low, pivot-1);
        quickSort(procs, pivot+1, high);
    }
}

void sortByArrivalTime(ProcInfo **procs, int numProcs) {
    quickSort(procs, 0, numProcs-1);   
}

void giveQuantaToProc(ProcInfo *proc, int curTime) {
    if(proc->lastRunTime != 0 && proc->lastRunTime != curTime-1) {
        // this process was preempted
        proc->totalWaitTime += curTime-proc->lastRunTime;
    }   
    if(proc->completedRunTime == 0) {
        proc->totalWaitTime += curTime-proc->arrivalTime;
        proc->startTime = curTime;
        proc->responseTime = proc->totalWaitTime;
    }
    proc->completedRunTime++;
    proc->lastRunTime = curTime;
}

void printProcs(ProcInfo *procs, int numProcs, FILE *stream) {
    int i;
    for(i = 0; i < numProcs; i++) {
        fprintf(stream, "Process id: %3d,\tatime: %.4f,\tpriority: %d,\ttotalRunTime: %4f\n", procs[i].id, procs[i].arrivalTime, procs[i].priority, procs[i].totalRunTime);
    }
}

void printResults(ProcInfo **finished, int finishedIndex, int *timeChart, int timeChartIndex, int numProcs, double timeSinceStart) {
    int i;
    double turnAroundTemp;

    double avgTurnAround = 0, avgWaiting = 0, avgResponse = 0;

    printf("\nTime chart:\n");
    for(i = 0; i < timeChartIndex; i++) {
        printf("%d ", timeChart[i]);
    }
    printf("\n\n");
    printf("Stats for procs:\n");
    for(i = 0; i < finishedIndex; i++) {
       turnAroundTemp = finished[i]->totalWaitTime+finished[i]->completedRunTime;

       avgTurnAround += turnAroundTemp;
       avgWaiting += finished[i]->totalWaitTime/finished[i]->timesWaited;
       avgResponse += finished[i]->responseTime;

       printf("Proc id: %3d\tTurnaround time: %.4f\tWaiting time: %.4f\tResponse time: %.4f\n", 
        finished[i]->id, turnAroundTemp, finished[i]->totalWaitTime/finished[i]->timesWaited, finished[i]->responseTime);
    }

    avgTurnAround /= finishedIndex;
    avgWaiting /= finishedIndex;
    avgResponse /= finishedIndex;

    printf("Average Turnaround time: %.4f\tAverage Waiting time: %.4f\tAverage Response time: %.4f\n", 
        avgTurnAround, avgWaiting, avgResponse);
    printf("Throughput: %.4f processes/quanta\n", numProcs/timeSinceStart);
}
