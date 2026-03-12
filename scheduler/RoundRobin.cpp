#include "Scheduler.h"

RoundRobin::RoundRobin(int quantum) : quantum_(quantum > 0 ? quantum : 1) {}

Process* RoundRobin::select(std::vector<Process*>& readyQueue, int /*currentTime*/) {
    if (readyQueue.empty()) {
        return nullptr;
    }

    Process* selected = readyQueue.front();
    readyQueue.erase(readyQueue.begin());
    return selected;
}
