#include "cpu/CPU.h"
#include "metrics/Metrics.h"
#include "scheduler/Scheduler.h"
#include "workload/WorkloadGenerator.h"

#include <iostream>
#include <memory>

int main() {
    std::cout << "Select Scheduling Algorithm\n\n"
              << "1. FCFS\n"
              << "2. SJF\n"
              << "3. SRTF\n"
              << "4. Round Robin\n"
              << "5. Priority\n\n"
              << "Choice: ";

    int choice = 0;
    std::cin >> choice;

    std::unique_ptr<Scheduler> scheduler;

    switch (choice) {
    case 1:
        scheduler = std::make_unique<FCFS>();
        break;
    case 2:
        scheduler = std::make_unique<SJF>();
        break;
    case 3:
        scheduler = std::make_unique<SRTF>();
        break;
    case 4: {
        std::cout << "Enter time quantum: ";
        int quantum = 1;
        std::cin >> quantum;
        scheduler = std::make_unique<RoundRobin>(quantum);
        break;
    }
    case 5:
        scheduler = std::make_unique<PriorityScheduler>();
        break;
    default:
        std::cout << "Invalid choice, defaulting to FCFS.\n";
        scheduler = std::make_unique<FCFS>();
        break;
    }

    std::cout << "Enter number of processes: ";
    int process_count = 0;
    std::cin >> process_count;

    if (process_count <= 0) {
        std::cout << "Process count must be positive.\n";
        return 1;
    }

    std::vector<Process> workload = generateWorkload(process_count);

    Metrics metrics;
    CPU cpu(1, scheduler.get(), &metrics);

    std::cout << "\nRunning simulation with " << scheduler->name() << "...\n";
    cpu.run(workload);
    metrics.print();

    std::cout << "\n## System Profiling\n\n"
              << "To view CPU performance statistics run:\n\n"
              << "/usr/lib/linux-tools/6.8.0-101-generic/perf stat ./scheduler_sim\n\n"
              << "Optional advanced profiling:\n\n"
              << "perf record ./scheduler_sim\n"
              << "perf report\n";

    return 0;
}
