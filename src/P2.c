// need at most 1000 process, and at least 10 processes because each process can have a total quanta from .1 to 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ProcInfo.h"
#include "FCFS.h"
#include "SJF.h"
#include "SRT.h"
#include "RR.h"
#include "HPF.h"

// this is (1000+10)/2
#define MAX_PROCS 1000
#define desiredQuanta 100

typedef struct Processes {
    int numProcs;
    ProcInfo *procs;
} Processes;

/* generates simulated processes based on the guidelines in the project manual
 * @retval a Processes struct where 
 *      numProcs is the number of valid processes that will fill 100 quanta
 *      procs is a heap allocated array of ProcInfo
 */
Processes *getProcesses() {
    int i;
    float summedTotalRunTime = 0;
    Processes *retval = (Processes *)malloc(sizeof(Processes));
    retval->procs = (ProcInfo *)malloc(MAX_PROCS*sizeof(ProcInfo));
    for(i = 0; i < MAX_PROCS && summedTotalRunTime < desiredQuanta; i++) {
    //for(i = 0; i < MAX_PROCS; i++) {
        retval->procs[i].id = i+1;
        retval->procs[i].arrivalTime = (rand()%100000)/1000.0;
        retval->procs[i].totalRunTime = (rand()%100+1)/10.0;
        retval->procs[i].completedRunTime = 0;
        retval->procs[i].totalWaitTime = 0;
        retval->procs[i].priority = rand()%NUM_PRIORITIES+1;
        summedTotalRunTime += retval->procs[i].totalRunTime;
    }
    retval->numProcs = i;
    return retval;
}

int main(int argc, char *argv[]) {
    srand(time(0));
    Processes *processes = getProcesses();

    sortByArrivalTime(&processes->procs, processes->numProcs);
    
    doFCFS(processes->procs, processes->numProcs);
    printf("\n");
    doSJF(processes->procs, processes->numProcs);
    printf("\n");
    doSRT(processes->procs, processes->numProcs);
    printf("\n");
    doRR(processes->procs, processes->numProcs);
    printf("\n");
    doHPF(processes->procs, processes->numProcs, 0);
    printf("\n");
    doHPF(processes->procs, processes->numProcs, 1);

    free(processes->procs);
    processes->procs = NULL;
    free(processes);
    processes = NULL;
}
