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

        Process* current = scheduler->select(ready, time);

        if(current){
            if(current->start_time == -1)
                current->start_time = time;

            current->remaining--;

            if(current->remaining == 0){
                current->completion_time = time + 1;
                completed++;

                int tat = current->completion_time - current->arrival;
                int wait = tat - current->burst;
                metrics->record(wait, tat);

                ready.erase(std::remove(ready.begin(), ready.end(), current), ready.end());
            }
        }

        time++;
    }
}
