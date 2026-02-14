#include "Metrics.h"

void Metrics::record(int wait, int tat){
    totalWaiting += wait;
    totalTurnaround += tat;
    completed++;
}

void Metrics::print(){
    std::cout<<"Avg Waiting: "<<(double)totalWaiting/completed<<std::endl;
    std::cout<<"Avg Turnaround: "<<(double)totalTurnaround/completed<<std::endl;
}
