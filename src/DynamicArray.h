#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "ProcInfo.h"
#define _INIT_DYNAMIC_ARRAY_SIZE 8

/* procs is an array of references, which represents the dynamic array
 * index is one location above the top of the dynamic array
 * size is the current size of the dynamic array
 * numElements is the number of elements in the dynamic array (ie index-1)
 */
typedef struct DynamicArray {
    ProcInfo **procs;
    int numElements;
    int size, index;
} DynamicArray;

/* Creates a dynamic array
 * @retval a DynamicArray allocated on the heap 
 */
DynamicArray *initializeDynamicArray();

/* Frees the memory of a dynamic array
 * @param s
 *      a DynamicArray that was initialized with initializeDynamicArray()
 */
void cleanupDynamicArray(DynamicArray *s);

/* Adds p to s and resizes s if necessary
 * @param s
 *      the DynamicArray to add p to
 * @param p
 *      the ProcInfo to add to s
 */
void addToDynamicArray(DynamicArray *s, ProcInfo *p);

/* returns the element at the top of the dynamic array, if there is one
 * @param s
 *      a reference to the dynamic array to retreive the data from
 *      the data will no longer be in the dynamic array when this function returns
 * @retval a reference to the data that was stored at the head of the dynamic array
 *      if there is no valid data in the queue, retval will be NULL
 *      it is up to the programmer to ensure that this return value is freed when it is no longer needed
 *      otherwiese there will be a memory leak
 */
ProcInfo *popDynamicArray(DynamicArray *s);

/* Convience function that prints the contents of the dynamic array
 * @param s
 *      the dynamic array to print the contents of
 * @param stream
 *      the stream to print to
 */
void printDynamicArray(DynamicArray *s, FILE *stream);

/* returns the process with the smallest remaining time in the dynamic array
 * @param s
 *      a reference to the dynamic array to retreive the data from
 *      the data will no longer be in the dynamic array when this function returns
 * @retval a reference to the process with the smallest remaining time that was stored in the dynamic array
 *      if there is no valid data in the queue, retval will be NULL
 *      it is up to the programmer to ensure that this return value is freed when it is no longer needed
 *      otherwiese there will be a memory leak
 *
 * note: will break the ordering of the things in the array, since it works by reordering them and then calling popDynamicArray()
 */
ProcInfo *getSmallestRemainingTime(DynamicArray* s);
#endif 
