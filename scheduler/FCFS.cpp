#include "Scheduler.h"

Process* FCFS::select(std::vector<Process*>& readyQueue, int /*currentTime*/) {
    if (readyQueue.empty()) {
        return nullptr;
    }

    Process* selected = readyQueue.front();
    readyQueue.erase(readyQueue.begin());
    return selected;
}
