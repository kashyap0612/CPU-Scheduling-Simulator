#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../process/Process.h"
#include <vector>

class Scheduler {
public:
    virtual Process* select(std::vector<Process*>& readyQueue, int currentTime) = 0;
    virtual bool isPreemptive() const { return false; }
    virtual int timeQuantum() const { return -1; }
    virtual const char* name() const = 0;
    virtual ~Scheduler() = default;
};

class FCFS : public Scheduler {
public:
    Process* select(std::vector<Process*>& readyQueue, int currentTime) override;
    const char* name() const override { return "FCFS"; }
};

class SJF : public Scheduler {
public:
    Process* select(std::vector<Process*>& readyQueue, int currentTime) override;
    const char* name() const override { return "SJF"; }
};

class SRTF : public Scheduler {
public:
    Process* select(std::vector<Process*>& readyQueue, int currentTime) override;
    bool isPreemptive() const override { return true; }
    const char* name() const override { return "SRTF"; }
};

class RoundRobin : public Scheduler {
public:
    explicit RoundRobin(int quantum);
    Process* select(std::vector<Process*>& readyQueue, int currentTime) override;
    bool isPreemptive() const override { return true; }
    int timeQuantum() const override { return quantum_; }
    const char* name() const override { return "Round Robin"; }

private:
    int quantum_;
};

class PriorityScheduler : public Scheduler {
public:
    Process* select(std::vector<Process*>& readyQueue, int currentTime) override;
    const char* name() const override { return "Priority"; }
};

#endif
