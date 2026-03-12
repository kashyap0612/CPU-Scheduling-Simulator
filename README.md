# CPU Scheduling Simulator (C++17)

A modular CPU scheduling simulator implemented in clean C++17, designed to run on Linux/WSL and compiled with a single `g++` command.

## Build

```bash
g++ -std=c++17 main.cpp cpu/*.cpp metrics/*.cpp workload/*.cpp scheduler/*.cpp -o scheduler_sim
```

## Run

```bash
./scheduler_sim
```

## Features

- Runtime scheduler selection from CLI:
  - FCFS
  - SJF (non-preemptive)
  - SRTF (preemptive)
  - Round Robin (configurable time quantum)
  - Priority Scheduling
- Workload generator for random process sets
- CPU simulation engine with modular scheduler interface
- Metrics report:
  - Average Waiting Time
  - Average Turnaround Time
  - Processes Completed
- Linux `perf` profiling usage instructions printed after simulation

## Project Structure

- `cpu/CPU.h`, `cpu/CPU.cpp` - CPU execution engine
- `scheduler/Scheduler.h`, `scheduler/*.cpp` - scheduler interface and algorithms
- `process/Process.h` - process model
- `metrics/Metrics.h`, `metrics/Metrics.cpp` - metrics tracking/reporting
- `workload/WorkloadGenerator.h`, `workload/WorkloadGenerator.cpp` - random workload generation
- `main.cpp` - CLI and simulation orchestration
