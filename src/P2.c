// need at most 1000 process, and at least 10 processes because each process can have a total quanta from .1 to 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ProcInfo.h"
//#include "FCFS.h"
#include "SJF.h"
#include "SRT.h"
#include "RR.h"
#include "HPF.h"

// this is (1000+10)/2
#define MAX_PROCS 1000
#define NUM_ALGS 8

char *helpText = "Usage:\n\t%s [algType | numRuns]\nWhere:\n\talgType is the name of an algorith to run. Possible options are:FCFS, SJF, SRT, RR, HPF_NO_PREEMPT, HPF_PREEMPT, HPF_NO_PREEMPT_AGING, or HPF_PREEMPT_AGING\n\n\tnumRuns is the number of times you want to run each algorithm in a row. In this case it will run all of the algoritms\n\nOnly one of the arguments is required.\n";

enum Algs {FCFS, SJF, SRT, RR, HPF_NO_PREEMPT, HPF_PREEMPT, HPF_NO_PREEMPT_AGING, HPF_PREEMPT_AGING}; 

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
    int i, temp = 0;
    float summedTotalRunTime = 0;
    Processes *retval = (Processes *)malloc(sizeof(Processes));
    retval->procs = (ProcInfo *)malloc(MAX_PROCS*sizeof(ProcInfo));
    for(i = 0; i < MAX_PROCS && summedTotalRunTime < desiredQuanta; i++) {
    //for(i = 0; i < MAX_PROCS; i++) {
        retval->procs[i].id = i+1;
        if(i == 0) {
            retval->procs[i].arrivalTime = 0;
        } else {
            // ensures processor is not unused for more than a single quanta between procs as most
            if(retval->procs[i-1].totalRunTime < 1) {
                temp = 1;
            } else {
                temp = (int)retval->procs[i-1].totalRunTime;
            }
            retval->procs[i].arrivalTime = retval->procs[i-1].arrivalTime
                +(rand()%temp);
        }
        retval->procs[i].totalRunTime = (rand()%100+1)/10.0;
        retval->procs[i].completedRunTime = 0;
        retval->procs[i].totalWaitTime = 0;
        retval->procs[i].priority = rand()%NUM_PRIORITIES+1;
        retval->procs[i].startTime = 0;
        retval->procs[i].responseTime = 0;
        retval->procs[i].timesWaited = 1;
        summedTotalRunTime += retval->procs[i].totalRunTime;
    }
    retval->numProcs = i;
    return retval;
}

/* runs the algorithm type with the processes
 * @param type
 *      a number from 0-NUM_ALGS, representing which algorithm to run
 * @param processes
 *      a reference to an array of processes to run the algorithm on
 */
void runProcesses(int type, Processes *processes) {
    switch(type) {
        case FCFS:
            //doFCFS(processes->procs, processes->numProcs);
            printf("\n");
            break;
        case SJF:
            doSJF(processes->procs, processes->numProcs);
            printf("\n");
            break;
        case SRT:
            doSRT(processes->procs, processes->numProcs);
            printf("\n");
            break;
        case RR:
            doRR(processes->procs, processes->numProcs);
            printf("\n");
            break;
        case HPF_NO_PREEMPT:
            doHPF(processes->procs, processes->numProcs, 0, 0);
            printf("\n");
            break;
        case HPF_PREEMPT:
            doHPF(processes->procs, processes->numProcs, 1, 0);
            printf("\n");
            break;
        case HPF_NO_PREEMPT_AGING:
            doHPF(processes->procs, processes->numProcs, 0, 1);
            printf("\n");
            break;
        case HPF_PREEMPT_AGING:
            doHPF(processes->procs, processes->numProcs, 1, 1);
            printf("\n");
            break;
    }
}

/* runs a specified algorithm, or runs all the algorithms a number of times
 * @param type
 *      a number from 0-NUM_ALGS, representing which algorithm to run
 *      if type < 0, then it will run all the algorithms -type number of times
 */
void run(int type) {
    int i, j;   
    Processes *processes = getProcesses();
    sortByArrivalTime(&processes->procs, processes->numProcs);

    if(type < 0) { 
        for(j = 0; j < NUM_ALGS; j++) { 
            for(i = 0; i > type; i--) {
                runProcesses(j, processes);
            }
        }
    } else {
        runProcesses(type, processes);
    }
    free(processes->procs);
    processes->procs = NULL;
    free(processes);
    processes = NULL;
}

void printHelpText(char *prgName) {
    fprintf(stderr, helpText, prgName);
}

int parseArgs(int argc, char *argv[]) {
    int type;
    if(argc < 2) {
        fprintf(stderr, "Not enough arguments.\n");
        printHelpText(argv[0]);
        exit(-1);
    } else if(argc > 2) {
        fprintf(stderr, "Too many arguements. ");
        printHelpText(argv[0]);
        exit(-1);
    }
    if((type = atoi(argv[1])) == 0) {
    //  user passed an algorithm name
        if(strcmp(argv[1], "FCFS") == 0) {
            type = FCFS;
        } else if(strcmp(argv[1], "SJF") == 0) {
            type = SJF;
        } else if(strcmp(argv[1], "SRT") == 0) { 
            type = SRT;
        } else if(strcmp(argv[1], "RR") == 0) {
            type = RR;
        } else if(strcmp(argv[1], "HPF_NO_PREEMPT") == 0) {
            type = HPF_NO_PREEMPT;
        } else if(strcmp(argv[1], "HPF_PREEMPT") == 0) {
            type = HPF_PREEMPT;
        } else if(strcmp(argv[1], "HPF_NO_PREEMPT_AGING") == 0) {
            type = HPF_NO_PREEMPT_AGING;
        } else if(strcmp(argv[1], "HPF_PREEMPT_AGING") == 0) {
            type = HPF_PREEMPT_AGING;
        } else {
            fprintf(stderr, "Unrecognized argument: %s\n", argv[1]);
            printHelpText(argv[0]);
            exit(-1);
        }
        return type;
    }
    return -type;
}

int main(int argc, char *argv[]) {
    int type = parseArgs(argc, argv);
    srand(time(0));
    run(type);
}
