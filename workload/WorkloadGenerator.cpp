#include "WorkloadGenerator.h"
#include <cstdlib>

std::vector<Process> generateWorkload(int n){
    std::vector<Process> p(n);

    for(int i=0;i<n;i++){
        p[i].pid = i;
        p[i].arrival = rand()%10;
        p[i].burst = 1 + rand()%10;
        p[i].remaining = p[i].burst;
        p[i].priority = rand()%5;
    }
    return p;
}
