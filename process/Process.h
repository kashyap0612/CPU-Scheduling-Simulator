#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid{};
    int arrival_time{};
    int burst_time{};
    int remaining_time{};
    int priority{};

    int start_time{-1};
    int completion_time{-1};
};

#endif
