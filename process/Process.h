#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority;

    int start_time = -1;
    int completion_time = 0;
};

#endif
