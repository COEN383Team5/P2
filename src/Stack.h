#ifndef STACK_H
#define STACK_H

#include "ProcInfo.h"
#define _INIT_STACK_SIZE 8

typedef struct Stack {
    ProcInfo **procs;
    int numElements;
    int size, index;
} Stack;

/* returns a heap allocated stack
 */
Stack *initializeStack();

void cleanupStack(Stack *s);

void addToStack(Stack *s, ProcInfo *p);

ProcInfo *popStack(Stack *s);

void printStack(Stack *s);
#endif 
