#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../process/Process.h"
#include <vector>

class Scheduler {
public:
    virtual Process* select(std::vector<Process*>& readyQueue, int currentTime) = 0;
    virtual ~Scheduler(){}
};

#endif
