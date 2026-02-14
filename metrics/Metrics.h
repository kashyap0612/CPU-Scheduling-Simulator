#ifndef METRICS_H
#define METRICS_H

#include <iostream>

class Metrics {
    long totalWaiting=0;
    long totalTurnaround=0;
    int completed=0;

public:
    void record(int wait, int tat);
    void print();
};

#endif
