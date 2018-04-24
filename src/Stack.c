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
