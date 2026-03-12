#include "Scheduler.h"
#include <algorithm>

Process* SRTF::select(std::vector<Process*>& readyQueue, int /*currentTime*/) {
    if (readyQueue.empty()) {
        return nullptr;
    }

    auto it = std::min_element(
        readyQueue.begin(), readyQueue.end(),
        [](const Process* a, const Process* b) {
            if (a->remaining_time == b->remaining_time) {
                return a->arrival_time < b->arrival_time;
            }
            return a->remaining_time < b->remaining_time;
        });

    Process* selected = *it;
    readyQueue.erase(it);
    return selected;
}
