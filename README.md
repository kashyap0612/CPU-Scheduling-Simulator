# CPU Scheduling Simulator (C++)

## Overview

This project implements a modular, multi-core CPU scheduling simulator in C++ that models classical operating system scheduling algorithms and measures their performance using standard scheduling metrics. The simulator supports multiple scheduling strategies and is designed with a layered architecture that separates workload generation, scheduling logic, CPU execution, and metrics computation.

The goal of the simulator is to analyze how different scheduling algorithms affect waiting time, turnaround time, response time, CPU utilization, and throughput under varying workloads.

---

## Features

* Support for multiple scheduling algorithms:

  * First Come First Serve (FCFS)
  * Shortest Job First (SJF)
  * Shortest Remaining Time First (SRTF)
  * Round Robin (RR)
  * Priority Scheduling (Preemptive / Non‑Preemptive)
* Multi-core CPU execution model
* Synthetic workload generation for controlled experiments
* Computation of scheduling performance metrics:

  * Waiting Time
  * Turnaround Time
  * Response Time
  * CPU Utilization
  * Throughput
* Modular architecture allowing easy extension of scheduling policies or workload models

---

## Project Structure

```
cpu_scheduler_sim/
│
├── main.cpp                     # Simulation entry point
│
├── process/                     # Process data structures
│   └── Process.h
│
├── scheduler/                   # Scheduling policy implementations
│   ├── Scheduler.h
│   ├── FCFS.cpp
│   ├── SJF.cpp
│   ├── SRTF.cpp
│   ├── RoundRobin.cpp
│   ├── Priority.cpp
│
├── cpu/                         # Multi-core CPU execution engine
│   ├── CPU.h
│   └── CPU.cpp
│
├── workload/                    # Workload and trace generation
│   ├── WorkloadGenerator.h
│   └── WorkloadGenerator.cpp
│
├── metrics/                     # Scheduling performance metrics
│   ├── Metrics.h
│   └── Metrics.cpp
│
└── README.md
```

---

## Build Instructions

From the project root directory:

```bash
g++ -std=c++17 main.cpp cpu/*.cpp metrics/*.cpp workload/*.cpp scheduler/*.cpp -o scheduler_sim
```

Run the simulator:

```bash
./scheduler_sim
```

---

## Simulation Flow

1. A workload generator creates a set of processes with arrival times, burst times, and priorities.
2. The selected scheduling algorithm determines which process should execute at each time step.
3. The CPU execution engine simulates execution across available cores.
4. Metrics are recorded during execution to compute scheduling performance statistics.
5. Final performance results are printed for analysis and comparison between scheduling strategies.

---

## Extending the Simulator

The modular design enables straightforward extensions:

* Add new scheduling algorithms by implementing the `Scheduler` interface.
* Introduce context-switch overhead modeling.
* Implement load balancing across CPU cores.
* Add real workload traces for experimental evaluation.
* Extend metrics to include fairness or starvation analysis.

---

## Purpose

This project demonstrates operating system scheduling behavior through a discrete-event simulation framework and serves as a platform for studying scheduling algorithm trade-offs, workload sensitivity, and multi-core execution effects.
