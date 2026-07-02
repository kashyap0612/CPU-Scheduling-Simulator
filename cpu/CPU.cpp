#include "CPU.h"
#include <algorithm>

CPU::CPU(int c, Scheduler* s, Metrics* m){
    cores = c;
    scheduler = s;
    metrics = m;
}

void CPU::run(std::vector<Process>& processes){

    int time = 0;
    int completed = 0;

    std::vector<Process*> ready;

    while(completed < processes.size()){

        for(auto &p : processes){
            if(p.arrival == time)
                ready.push_back(&p);
        }

        std::vector<Process*> running_processes;
        std::vector<Process*> temp_ready = ready;
        bool isPreemptive = false;

        for (int c = 0; c < cores; c++) {
            if (temp_ready.empty()) break;

            size_t sizeBefore = temp_ready.size();
            Process* lastBefore = temp_ready.back();

            Process* p = scheduler->select(temp_ready, time);
            if (p) {
                running_processes.push_back(p);

                // Auto-detect if scheduler is preemptive (e.g. Round Robin) by checking if 
                // the selected process was rotated to the back of the ready queue.
                if (temp_ready.size() == sizeBefore && temp_ready.back() == p && lastBefore != p) {
                    isPreemptive = true;
                }

                // Remove from temp_ready so other cores do not select it
                temp_ready.erase(std::remove(temp_ready.begin(), temp_ready.end(), p), temp_ready.end());
            }
        }

        // Reconstruct main ready queue:
        // Preemptive (e.g., RR) moves running processes to the back.
        // Non-preemptive (e.g., FCFS) keeps running processes at the front.
        if (isPreemptive) {
            ready = temp_ready;
            ready.insert(ready.end(), running_processes.begin(), running_processes.end());
        } else {
            ready = running_processes;
            ready.insert(ready.end(), temp_ready.begin(), temp_ready.end());
        }

        std::vector<Process*> finished;
        for (Process* p : running_processes) {
            if (p->start_time == -1) {
                p->start_time = time;
            }
            p->remaining--;
            if (p->remaining == 0) {
                finished.push_back(p);
            }
        }

        for (Process* p : finished) {
            p->completion_time = time + 1;
            completed++;

            int tat = p->completion_time - p->arrival;
            int wait = tat - p->burst;
            metrics->record(wait, tat);

            ready.erase(std::remove(ready.begin(), ready.end(), p), ready.end());
        }

        time++;
    }
}
