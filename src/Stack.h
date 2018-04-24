#ifndef STACK_H
#define STACK_H

#include "ProcInfo.h"
#define _INIT_STACK_SIZE 8

/* procs is an array of references, which represents the stack
 * index is one location above the top of the stack
 * size is the current size of the stack
 * numElements is the number of elements in the stack (ie index-1)
 */
typedef struct Stack {
    ProcInfo **procs;
    int numElements;
    int size, index;
} Stack;

/* Creates a stack
 * @retval a Stack allocated on the heap 
 */
Stack *initializeStack();

/* Frees the memory of a stack
 * @param s
 *      a Stack that was initialized with initializeStack()
 */
void cleanupStack(Stack *s);

/* Adds p to s and resizes s if necessary
 * @param s
 *      the Stack to add p to
 * @param p
 *      the ProcInfo to add to s
 */
void addToStack(Stack *s, ProcInfo *p);

/* returns the element at the top of the stack, if there is one
 * @param s
 *      a reference to the stack to retreive the data from
 *      the data will no longer be in the stack when this function returns
 * @retval a reference to the data that was stored at the head of the stack
 *      if there is no valid data in the queue, retval will be NULL
 *      it is up to the programmer to ensure that this return value is freed when it is no longer needed
 *      otherwiese there will be a memory leak
 */
ProcInfo *popStack(Stack *s);

/* Convience function that prints the contents of the stack
 * @param s
 *      the stack to print the contents of
 * @param stream
 *      the stream to print to
 */
void printStack(Stack *s, FILE *stream);
#endif 
