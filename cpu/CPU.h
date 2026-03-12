#ifndef CPU_H
#define CPU_H

#include "../metrics/Metrics.h"
#include "../scheduler/Scheduler.h"
#include <vector>

class CPU {
public:
    CPU(int cores, Scheduler* scheduler, Metrics* metrics);
    void run(std::vector<Process>& processes);

private:
    int cores_;
    Scheduler* scheduler_;
    Metrics* metrics_;
};

#endif
