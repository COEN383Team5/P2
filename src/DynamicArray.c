#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.h"

void resizeDynamicArray(DynamicArray *s) {
    ProcInfo **temp = (ProcInfo **)calloc(s->size<<1, sizeof(ProcInfo*));
    memcpy(temp, s->procs, sizeof(ProcInfo *)*s->size);
    s->size <<= 1;
    free(s->procs);
    s->procs = temp;
}

DynamicArray *initializeDynamicArray() {
    DynamicArray *s = (DynamicArray *) malloc(sizeof(DynamicArray));
    s->procs = (ProcInfo **)calloc(_INIT_DYNAMIC_ARRAY_SIZE, sizeof(ProcInfo*));
    s->numElements = 0;
    s->size = _INIT_DYNAMIC_ARRAY_SIZE;
    s->index = 0;
    return s;
}

void cleanupDynamicArray(DynamicArray *s) {
    free(s->procs);
    free(s);
}

void addToDynamicArray(DynamicArray *s, ProcInfo *p) {
    if(s->numElements+1 > s->size) {
       resizeDynamicArray(s); 
    }
    s->procs[s->index++] = p;
    s->numElements++;
}

void sortByRemainingTime(ProcInfo **procs, int numProcs) {
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

ProcInfo *getSmallestRemainingTime(DynamicArray *s) {
    sortByRemainingTime(s->procs, s->numElements);
    return popDynamicArray(s);
}

ProcInfo *popDynamicArray(DynamicArray *s) {
    if(s->numElements > 0) {
        s->numElements--;
        s->index--;
        return s->procs[s->index];
    } else {
        return NULL;
    }
}

void printDynamicArray(DynamicArray *s, FILE *stream) {
    int i;
    fprintf(stream, "Printing dynamic array with elements %d, %d: ", s->numElements, s->index);
    for(i = s->index-1; i >= 0; i--) {
        fprintf(stream, "%d ", s->procs[i]->id);
    }
    fprintf(stream, "\n");
}
