#ifndef PROCINFO_H
#define PROCINFO_H
#include <stdio.h>

#define NUM_PRIORITIES 4

typedef struct ProcInfo {
    int id; 
    double arrivalTime;
    double totalRunTime;
    // completedRunTime is the amount of time that this process has be allowed to run, starts at 0 and ends at >= totalRunTime
    double completedRunTime;
    int totalWaitTime;
    int priority;
    // the last time it started running
    int lastRunTime;
} ProcInfo;

int partition(ProcInfo **procs, int low, int high); 

void quickSort(ProcInfo **procs, int low, int high);

void sortByArrivalTime(ProcInfo **procs, int numProcs); 

void printProcs(ProcInfo *procs, int numProcs, FILE *stream); 

void printProcsWithStats(ProcInfo *procs, int numProcs, FILE *stream); 

void printResults(ProcInfo **finished, int finishedIndex, int *timeChart, int timeChartIndex, int numProcs, double timeSinceStart);

#endif
