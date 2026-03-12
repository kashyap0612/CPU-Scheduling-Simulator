#include "Scheduler.h"
#include <algorithm>

Process* SJF::select(std::vector<Process*>& readyQueue, int /*currentTime*/) {
    if (readyQueue.empty()) {
        return nullptr;
    }

    auto it = std::min_element(
        readyQueue.begin(), readyQueue.end(),
        [](const Process* a, const Process* b) {
            if (a->burst_time == b->burst_time) {
                return a->arrival_time < b->arrival_time;
            }
            return a->burst_time < b->burst_time;
        });

    Process* selected = *it;
    readyQueue.erase(it);
    return selected;
}
