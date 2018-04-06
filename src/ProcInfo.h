#ifndef PROCINFO_H
#define PROCINFO_H

#define NUM_PRIORITIES 4

typedef struct ProcInfo {
    int id; 
    float arrivalTime;
    float totalRunTime;
    // completedRunTime is the amount of time that this process has be allowed to run, starts at 0 and ends at >= totalRunTime
    float completedRunTime;
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

#endif
