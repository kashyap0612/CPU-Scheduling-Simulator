#include "WorkloadGenerator.h"
#include <random>

std::vector<Process> generateWorkload(int n) {
    std::vector<Process> processes;
    processes.reserve(n);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> arrival_dist(0, 10);
    std::uniform_int_distribution<int> burst_dist(1, 15);
    std::uniform_int_distribution<int> priority_dist(1, 10);

    for (int i = 0; i < n; ++i) {
        Process p;
        p.pid = i + 1;
        p.arrival_time = arrival_dist(rng);
        p.burst_time = burst_dist(rng);
        p.remaining_time = p.burst_time;
        p.priority = priority_dist(rng);
        processes.push_back(p);
    }

    return processes;
}
