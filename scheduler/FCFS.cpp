#include "Scheduler.h"

class FCFS : public Scheduler {
public:
    Process* select(std::vector<Process*>& rq, int currentTime) override {
        if(rq.empty()) return nullptr;
        return rq.front();
    }
};
