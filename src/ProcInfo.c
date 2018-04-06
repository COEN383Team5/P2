#include <stdio.h>
#include <stdlib.h>
#include "ProcInfo.h"

int partition(ProcInfo **procs, int low, int high) {
    int j, i = (low-1);
    ProcInfo temp;
    float pivot = (*procs)[high].arrivalTime;
    for(j = low; j < high; j++) {
        if((*procs)[j].arrivalTime <= pivot)  {
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
        fprintf(stream, "Process id: %3d,\tatime: %.4f,\tttime %.1f,\tctime %.4f,\tpriority: %d\n", procs[i].id, procs[i].arrivalTime, procs[i].totalRunTime, procs[i].completedRunTime, procs[i].priority);
    }
}
