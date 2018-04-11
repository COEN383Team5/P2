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

void printProcs(ProcInfo *procs, int numProcs, FILE *stream) {
    int i;
    for(i = 0; i < numProcs; i++) {
        fprintf(stream, "Process id: %3d,\tatime: %.4f,\tpriority: %d\n", procs[i].id, procs[i].arrivalTime, procs[i].priority);
    }
}

void printResults(ProcInfo **finished, int finishedIndex, int *timeChart, int timeChartIndex, int numProcs, double timeSinceStart) {
    int i;
    double waitTimeTemp, turnAroundTemp;
    printf("\nTime chart:\n");
    for(i = 0; i < timeChartIndex; i++) {
        printf("%d ", timeChart[i]);
    }
    printf("\n\n");
    printf("Stats for procs:\n");
    for(i = 0; i < finishedIndex; i++) {
       waitTimeTemp = ((double)finished[i]->totalWaitTime)/ceil(finished[i]->totalRunTime);
       turnAroundTemp = finished[i]->totalWaitTime+finished[i]->completedRunTime;

       printf("Proc id: %3d,\tAverage turnaround time: %.4f,\tAverage waiting time: %.4f\tAverage response time %.4f\n", finished[i]->id, turnAroundTemp, waitTimeTemp, finished[i]->responseTime);
    }
    printf("Throughput: %.4f processes/quanta\n", numProcs/timeSinceStart);
}
