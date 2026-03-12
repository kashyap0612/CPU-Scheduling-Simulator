#include "CPU.h"

#include <algorithm>

CPU::CPU(int cores, Scheduler* scheduler, Metrics* metrics)
    : cores_(std::max(1, cores)), scheduler_(scheduler), metrics_(metrics) {}

void CPU::run(std::vector<Process>& processes) {
    int current_time = 0;
    int completed = 0;

    std::vector<Process*> ready_queue;
    std::vector<Process*> running(cores_, nullptr);
    std::vector<int> slice_used(cores_, 0);

    while (completed < static_cast<int>(processes.size())) {
        for (auto& process : processes) {
            if (process.arrival_time == current_time) {
                ready_queue.push_back(&process);
            }
        }

        if (scheduler_->isPreemptive()) {
            for (int core = 0; core < cores_; ++core) {
                if (running[core] != nullptr) {
                    ready_queue.push_back(running[core]);
                    running[core] = nullptr;
                    slice_used[core] = 0;
                }
            }
        }

        for (int core = 0; core < cores_; ++core) {
            if (running[core] == nullptr) {
                running[core] = scheduler_->select(ready_queue, current_time);
                slice_used[core] = 0;
                if (running[core] != nullptr && running[core]->start_time == -1) {
                    running[core]->start_time = current_time;
                }
            }
        }

        bool made_progress = false;

        for (int core = 0; core < cores_; ++core) {
            Process* process = running[core];
            if (process == nullptr) {
                continue;
            }

            made_progress = true;
            --process->remaining_time;
            ++slice_used[core];

            if (process->remaining_time == 0) {
                process->completion_time = current_time + 1;
                const int turnaround = process->completion_time - process->arrival_time;
                const int waiting = turnaround - process->burst_time;
                metrics_->record(waiting, turnaround);

                running[core] = nullptr;
                slice_used[core] = 0;
                ++completed;
                continue;
            }

            const int quantum = scheduler_->timeQuantum();
            if (quantum > 0 && slice_used[core] >= quantum) {
                ready_queue.push_back(process);
                running[core] = nullptr;
                slice_used[core] = 0;
            }
        }

        if (!made_progress && ready_queue.empty()) {
            ++current_time;
            continue;
        }

        ++current_time;
    }
}
