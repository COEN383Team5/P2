#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "SRT.h"

void doSRT(ProcInfo *procs, int numProcs) {
    DynamicArray *waitingProcs;
    Stack *preemptCandidates;
    int timeChart[10240];
    ProcInfo *temp = NULL, *curRun = NULL, procCopy[numProcs];
    ProcInfo **finished = (ProcInfo**)calloc(numProcs,sizeof(ProcInfo*));
    int finishedIndex = 0, nextProc = 0, curTime = 0, chartIndex = 0;

    memcpy(procCopy, procs, numProcs*sizeof(ProcInfo));
    waitingProcs = initializeDynamicArray();
    preemptCandidates = initializeStack();

    printf("Starting shortest remaining time algorithm\n\n");
    printProcs(procs, numProcs, stdout);

    // only quit when there are not more processes to run
    while(1) {
        if(curTime < desiredQuanta && nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
        	// handle the incoming process
            if (curRun != NULL) {
                while(nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
                    addToStack(preemptCandidates, &procCopy[nextProc++]);
                }

                // check if the currently running process needs to be preempted by any of the incoming processes
                while((temp = popStack(preemptCandidates)) != NULL) {
                    if (temp->totalRunTime < curRun->totalRunTime-curRun->completedRunTime) {
                        curRun->timesWaited++;
                        addToDynamicArray(waitingProcs, curRun);
                        printf("%d was preempted by %d\n", curRun->id, temp->id);
                        curRun = temp;
                        temp = NULL;
                    } else {
                        addToDynamicArray(waitingProcs, temp);
                        temp = NULL;
                    }
                }

            } else {
                while(nextProc < numProcs && procCopy[nextProc].arrivalTime <= curTime) {
                    addToDynamicArray(waitingProcs, &procCopy[nextProc++]); 
                }
            }
        }
        if(curRun == NULL) {
        	// schedule the process with the shortest remainging time; quit if done
            if((temp = getSmallestRemainingTime(waitingProcs)) != NULL) {
                curRun = temp;
                temp = NULL;
            } else if((curRun = getSmallestRemainingTime(waitingProcs)) == NULL && curTime > desiredQuanta) {
                // no more procs to run
                break;
            } 
        }
        if(curRun != NULL) {
        	// run the process for this quanta
            timeChart[chartIndex++] = curRun->id;
            giveQuantaToProc(curRun, curTime);
            if(curRun->completedRunTime >= curRun->totalRunTime) {
                finished[finishedIndex++] = curRun;
                curRun = NULL;
            }
        } else {
            fprintf(stderr, "Processor was unused during %d quantum\n", curTime);
        }

        curTime++;
    }

    printResults(finished, finishedIndex, timeChart, chartIndex, numProcs, curTime);
    cleanupDynamicArray(waitingProcs);
    waitingProcs = NULL;
    cleanupStack(preemptCandidates);
    preemptCandidates = NULL;
//  note that finished[i] doesn't have to be freed because it points to a part of procCopy
    free(finished);
    finished = NULL;
}
