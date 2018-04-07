This repo has code to simulate a scheduler using different algorithms. It was made to satisfy an assignment for COEN383 Advanced Operating Systems at Santa Clara University. 

To compile on a unix system:
    make

Usage:
    bin/P2 [algType | numRuns]

    Where:
        algType is the name of an algorith to run. Possible options are:FCFS, SJF, SRT, RR, HPF_NO_PREEMPT, or HPF_PREEMPT

        numRuns is the number of times you want to run each algorithm in a row. In this case it will run all of the algoritms

    Only one of the arguments is required.

Most complicated headers have comments for their functions. The assignment description is included in Project-2.pdf.
