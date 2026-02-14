#ifndef CPU_H
#define CPU_H

#include "../scheduler/Scheduler.h"
#include "../metrics/Metrics.h"
#include <vector>

class CPU {
    int cores;
    Scheduler* scheduler;
    Metrics* metrics;

public:
    CPU(int c, Scheduler* s, Metrics* m);
    void run(std::vector<Process>& processes);
};

#endif
