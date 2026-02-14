#include "cpu/CPU.h"
#include "metrics/Metrics.h"
#include "workload/WorkloadGenerator.h"
#include "scheduler/FCFS.cpp"

int main(){

    Metrics m;
    Scheduler* s = new FCFS();

    CPU cpu(4, s, &m);

    auto processes = generateWorkload(50);

    cpu.run(processes);

    m.print();
}
