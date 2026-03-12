#include "Scheduler.h"
#include <algorithm>

Process* PriorityScheduler::select(std::vector<Process*>& readyQueue, int /*currentTime*/) {
    if (readyQueue.empty()) {
        return nullptr;
    }

    auto it = std::min_element(
        readyQueue.begin(), readyQueue.end(),
        [](const Process* a, const Process* b) {
            if (a->priority == b->priority) {
                return a->arrival_time < b->arrival_time;
            }
            return a->priority < b->priority;
        });

    Process* selected = *it;
    readyQueue.erase(it);
    return selected;
}
