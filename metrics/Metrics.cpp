#include "Metrics.h"
#include <iostream>

void Metrics::record(int wait_time, int turnaround_time) {
    total_waiting_time_ += wait_time;
    total_turnaround_time_ += turnaround_time;
    ++completed_processes_;
}

void Metrics::print() const {
    std::cout << "\n## Scheduling Results\n\n";

    if (completed_processes_ == 0) {
        std::cout << "Average Waiting Time: 0\n";
        std::cout << "Average Turnaround Time: 0\n";
        std::cout << "Processes Completed: 0\n";
        return;
    }

    const double average_wait = static_cast<double>(total_waiting_time_) / completed_processes_;
    const double average_turnaround = static_cast<double>(total_turnaround_time_) / completed_processes_;

    std::cout << "Average Waiting Time: " << average_wait << "\n";
    std::cout << "Average Turnaround Time: " << average_turnaround << "\n";
    std::cout << "Processes Completed: " << completed_processes_ << "\n";
}
