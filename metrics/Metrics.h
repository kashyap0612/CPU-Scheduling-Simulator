#ifndef METRICS_H
#define METRICS_H

class Metrics {
public:
    void record(int wait_time, int turnaround_time);
    void print() const;

private:
    long total_waiting_time_{0};
    long total_turnaround_time_{0};
    int completed_processes_{0};
};

#endif
