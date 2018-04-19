#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HPF.h"

void doHPF(ProcInfo *procs, int numProcs, int preemptive) {

	printf("Starting highest priority first algorithm");
    if(preemptive) {
        printf(" with preemption\n\n");
    } else {
        printf(" without preemption\n\n");
    }
	printProcs(procs, numProcs, stdout);
    
}
