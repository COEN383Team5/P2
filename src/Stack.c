#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

void resize(Stack *s) {
    ProcInfo **temp = (ProcInfo **)calloc(s->size<<1, sizeof(ProcInfo*));
    memcpy(temp, s->procs, sizeof(ProcInfo *)*s->size);
    s->size <<= 1;
    free(s->procs);
    s->procs = temp;
}

Stack *initializeStack() {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->procs = (ProcInfo **)calloc(_INIT_STACK_SIZE, sizeof(ProcInfo*));
    s->numElements = 0;
    s->size = _INIT_STACK_SIZE;
    s->index = 0;
    return s;
}

void cleanupStack(Stack *s) {
    free(s->procs);
    free(s);
}

void addToStack(Stack *s, ProcInfo *p) {
    if(s->numElements+1 > s->size) {
       resize(s); 
    }
    s->procs[s->index++] = p;
    s->numElements++;
}

/* int stackPartition(ProcInfo **procs, int low, int high) {
    int j, i = (low-1);
    ProcInfo temp;
    double pivotVal = ((*procs)[high].totalRunTime - (*procs)[high].completedRunTime);
    for(j = low; j < high; j++) {
        if((*procs)[j].totalRunTime - (*procs)[high].completedRunTime <= pivotVal)  {
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

void quickStackSort(ProcInfo **procs, int low, int high) {
    if(low < high) {
        int pivot = stackPartition(procs, low, high);
        quickStackSort(procs, low, pivot-1);
        quickStackSort(procs, pivot+1, high);
    }
} */

void sortByRemainingTime(ProcInfo **procs, int numProcs) {
    // quickStackSort(procs, 0, numProcs-1);
    
    int i, j, m;

    ProcInfo* temp;

    for(i = 0; j < numProcs; i++) {
        for (j = i, m = i; j < numProcs; j++) {
            if (((*procs)[j].totalRunTime - (*procs)[j].completedRunTime) > ((*procs)[m].totalRunTime - (*procs)[m].completedRunTime)) {
                m = j;
            }
        }

        temp = procs[i];
        procs[i] = procs[m];
        procs[m] = temp;
    }
}



/* ProcInfo *getSmallestRemainingTimeOnStack(Stack *s) {
    if(s->numElements > 0) {
        ProcInfo *shortest = s->procs[0];
        assert(s->procs[0] != NULL);
        float temp = s->procs[0]->totalRunTime - s->procs[0]->completedRunTime;
        float shortestVal = temp;
        int indexOfShortest = 0, i;

        for (i = 1; i < s->numElements; i++) {
            assert(s->procs[i] != NULL);

            temp = s->procs[i]->totalRunTime - s->procs[i]->completedRunTime;
            if(shortestVal > temp) {
                shortestVal = temp;
                indexOfShortest = i;
                shortest = s->procs[i];
            }
        }


        s->procs[indexOfShortest] = s->procs[s->index];
        s->index--;
        s->numElements--;
        return shortest;
    } else {
        return NULL;
    }
} */

ProcInfo *getSmallestRemainingTimeOnStack(Stack *s) {
    sortByRemainingTime(s->procs, s->numElements);
    return popStack(s);
}

ProcInfo *popStack(Stack *s) {
    if(s->numElements > 0) {
        s->numElements--;
        s->index--;
        return s->procs[s->index];
    } else {
        return NULL;
    }
}

void printStack(Stack *s, FILE *stream) {
    int i;
    fprintf(stream, "Printing stack with elements %d, %d: ", s->numElements, s->index);
    for(i = s->index-1; i >= 0; i--) {
        fprintf(stream, "%d ", s->procs[i]->id);
    }
    fprintf(stream, "\n");
}
