#include "Scheduler.h"

class RoundRobin : public Scheduler {
public:
    Process* select(std::vector<Process*>& rq, int currentTime) override {
        if(rq.empty()) return nullptr;
        Process* p = rq.front();
        rq.erase(rq.begin());
        rq.push_back(p);
        return p;
    }
};
