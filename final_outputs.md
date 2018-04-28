# Overview  
This file contains the final statistics for all 8 of the algorithms we implemented. Each algorithm was tested 5 times with random data; the numbers herein are averages of those five runs.  
The outputs for each individual run of the algorithm are contained in the outputs directory, and are labeled with the algorithm used and the run number.  
Note that for HPF, priority 1 is the highest priority, and priority 4 is the lowest.

# First-come First-serve (FCFS)  
Average turnaround time: 39.91688 quanta  
Average waiting time: 34.12654 quanta  
Average response time: 34.12654 quanta  
Average throughput: 0.19036 processes/quanta  


# Shortest Job First (SJF)    
Average turnaround time: 26.65444 quanta  
Average waiting time: 21.76286 quanta  
Average response time: 21.76286 quanta  
Average throughput: 0.21562 processes/quanta  


# Shortest Remaining Time (SRT)  
Average turnaround time: 28.27554 quanta  
Average waiting time: 22.44842 quanta  
Average response time: 22.52654 quanta  
Average throughput: 0.18588 processes/quanta  


# Round Robin (RR)  
Average turnaround time: 57.54676 quanta  
Average waiting time: 51.51446 quanta  
Average response time: 7.74492 quanta  
Average throughput: 0.16958 proccesses/quanta  


# Highest Priority First, Non-preemptive (HPF NOPREEMPT)  
## Overall  
Average turnaround time: 46.14846 quanta  
Average waiting time: 40.71518 quanta  
Average response time: 40.71518 quanta  
Average throughput: 0.18584 processes/quanta  

## Priority 1  
Average turnaround time: 13.73 quanta  
Average waiting time: 8.775 quanta  
Average response time: 8.775 quanta  
Average throughput: 0.14396 processes/quanta  

## Priority 2  
Average turnaround time: 29.86666 quanta  
Average waiting time: 25.28334 quanta  
Average response time: 25.28334 quanta  
Average throughput: 0.07976 processes/quanta  

## Priority 3  
Average turnaround time: 56.90002 quanta  
Average waiting time: 52.81166 quanta  
Average response time: 52.81166 quanta  
Average throughput: 0.06386 processes/quanta  

## Priority 4  
Average turnaround time: 81.2978 quanta  
Average waiting time: 77.22444 quanta  
Average response time: 77.22444 quanta  
Average throughput: 0.04918 processes/quanta  


# Highest Priority First, Preemptive (HPF PREEMPT)
## Overall  
Average turnaround time: 41.26998 quanta  
Average waiting time: 35.4052 quanta  
Average response time: 35.44252 quanta  
Average throughput: 0.181 processes/quanta  

## Priority 1  
Average turnaround time: 8.17142 quanta  
Average waiting time: 4.4 quanta  
Average response time: 4.4 quanta  
Average throughput: 0.12804 processes/quanta  

## Priority 2  
Average turnaround time: 28.33214 quanta  
Average waiting time: 22.55278 quanta  
Average response time: 22.78928 quanta  
Average throughput: 0.10872 processes/quanta  

## Priority 3  
Average turnaround time: 49.91666 quanta  
Average waiting time: 44.46906 quanta  
Average response time: 44.43572 quanta  
Average throughput: 0.04376 processes/quanta  

## Priority 4  
Average turnaround time: 89.07334 quanta  
Average waiting time: 84.80668 quanta  
Average response time: 84.80668 quanta  
Average throughput: 0.03928 processes/quanta  


# Highest Priority First, Non-preemptive, with aging (HPF NOPREEMPT AGING)  
## Overall  
Average turnaround time: 44.42294 quanta  
Average waiting time: 38.70664 quanta  
Average response time: 38.70664 quanta  
Average throughput: 0.17766 processes/quanta  

## Priority 1  
Average turnaround time: 44.90114 quanta  
Average waiting time: 40.2972 quanta  
Average response time: 40.2972 quanta  
Average throughput: 7.8917 processes/quanta  

## Priority 2  
Average turnaround time: 15.208325 quanta  
Average waiting time: 8.5 quanta  
Average response time: 8.5 quanta  
Average throughput: 0.099425 processes/quanta  

## Priority 3  
Average turnaround time: 66 quanta  
Average waiting time: 59 quanta  
Average response time: 59 quanta  
Average throughput: 0.0092 processes/quanta  

## Priority 4  
Average turnaround time: NaN quanta  
Average waiting time: NaN quanta  
Average response time: NaN quanta  
Average throughput: NaN processes/quanta  


# Highest Priority First, Preemptive, with aging (HPF PREEMPT AGING)  
## Overall  
Average turnaround time: 45.46748 quanta  
Average waiting time: 40.25528 quanta  
Average response time: 40.2528 quanta  
Average throughput: 0.19912 processes/quanta  

## Priority 1  
Average turnaround time: 48.40918 quanta  
Average waiting time: 44.2042 quanta  
Average response time: 44.2042 quanta  
Average throughput: 0.1831 processes/quanta  

## Priority 2  
Average turnaround time: 2 quanta  
Average waiting time: 0.5 quanta  
Average response time: 0.5 quanta  
Average throughput: 0.4 processes/quanta  

## Priority 3  
Average turnaround time: 15.1 quanta  
Average waiting time: 10.4 quanta  
Average response time: 10.4 quanta  
Average throughput: 0.1343 processes/quanta  

## Priority 4  
Average turnaround time: 8 quanta  
Average waiting time: 1.16665 quanta  
Average response time: 1 quanta  
Average throughput: 0.14545 processes/quanta  
