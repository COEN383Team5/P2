#ifndef PROCINFO_H
#define PROCINFO_H
#include <stdio.h>

#define NUM_PRIORITIES 4
#define desiredQuanta 100
#define TIME_CHART_SIZE 10240

typedef struct ProcInfo {
    int id; 
    double arrivalTime;
    double totalRunTime;
    // completedRunTime is the amount of time that this process has be allowed to run, starts at 0 and ends at >= totalRunTime
    double completedRunTime;
    double startTime;
    double responseTime;
    double totalWaitTime;
    int priority;
    int timesWaited;
    // the last time it started running
    int lastRunTime;
} ProcInfo;

/* quicksort helper function
 * @param procs
 *      a reference to the array of processes to sort by arrival time
 * @param low
 *      the lowest index being sorted during this call to partition
 * @param high
 *      the highest index being sorted during this call to partition
 */
int partition(ProcInfo **procs, int low, int high); 

/* sorts procs by arrival time
 * @param procs
 *      a reference to the array of processes to sort by arrival time
 * @param low
 *      the lowest index being sorted during this call to partition
 * @param high
 *      the highest index being sorted during this call to partition
 */
void quickSort(ProcInfo **procs, int low, int high);

/* convience function to call quicksort(3) to sort procs by arrival time
 * @param procs
 *      a reference to the array of processes to sort by arrival time
 * @param numProcs
 *      the number of ProcInfos in procs
 */
void sortByArrivalTime(ProcInfo **procs, int numProcs); 

/* Handles giving a quanta to a single ProcInfo
 * @param proc
 *      a reference to the process to give a quanta to
 * @param curTime
 *      the current running time in the simulation, which is going to be given to proc
 */
void giveQuantaToProc(ProcInfo *proc, int curTime);

/* convience function to print information about all the ProcInfos in procs
 * @param procs
 *      an array of ProcInfos to print the information of
 * @param numProcs
 *      the number of ProcInfos in procs
 * @param stream
 *      the stream to print to
 */
void printProcs(ProcInfo *procs, int numProcs, FILE *stream); 

/* convience function to print information about ProcInfos and the stats of them running
 * @param procs
 *      an array of ProcInfos to print the information of
 * @param numProcs
 *      the number of ProcInfos in procs
 * @param stream
 *      the stream to print to
 */
void printProcsWithStats(ProcInfo *procs, int numProcs, FILE *stream); 

/* convience function to print the total information about the running of a ProcInfo array
 * @param finished
 *      an array of references to ProcInfos to print the information of
 * @param finishedIndex
 *      the size of finished
 * @param timeChart
 *      the time chart associated with the finished processes
 * @param timeChartIndex
 *      the size of timeChart
 * @param numProcs
 *      the number of ProcInfos in finished
 *      this is used to calculate throughput
 * @param timeSinceStart
 *      the total run time of all the ProcInfos
 *      used to calculate throughput
 */
void printResults(ProcInfo **finished, int finishedIndex, int *timeChart, int timeChartIndex, int numProcs, double timeSinceStart);

#endif
