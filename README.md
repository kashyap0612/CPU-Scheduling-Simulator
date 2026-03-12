# CPU Scheduling Simulator (C++)

```
$ g++ -std=c++17 main.cpp cpu/*.cpp metrics/*.cpp workload/*.cpp scheduler/*.cpp -o scheduler_sim
$ perf stat ./scheduler_sim

Select Scheduling Algorithm

1. FCFS
2. SJF
3. SRTF
4. Round Robin
5. Priority

Choice: 5
Enter number of processes: 1500

Running simulation with Priority...

## Scheduling Results

Average Waiting Time: 6001.95
Average Turnaround Time: 6009.99
Processes Completed: 1500

## System Profiling

 Performance counter stats for './scheduler_sim':

 task-clock:        199.90 ms
 instructions:   1,452,277,007
 cycles:           686,367,032
 IPC:                    2.12
 branches:        240,017,097
 branch-misses:        0.11%

 elapsed time:        10.33 s
 user CPU time:        0.19 s
```

---

# Why I Built This

I wanted to understand **how operating systems schedule processes** and how different scheduling policies affect system performance.

Textbooks describe scheduling algorithms like FCFS, SJF, SRTF, Round Robin and Priority scheduling, but it is difficult to develop intuition about them without seeing how they behave on real workloads.

So instead of only studying the algorithms theoretically, I built a **CPU scheduling simulator in C++** that allows different scheduling policies to be tested against a configurable workload of processes.

The goal was to observe:

* how scheduling policy changes waiting and turnaround time
* how the ready queue evolves during execution
* how scheduling decisions translate into actual CPU instructions when profiled with Linux `perf`

---

# Core Idea of the Simulator

The simulator models a CPU scheduler using a **discrete time-step simulation**.

At every simulated time unit:

1. Newly arrived processes are added to the ready queue
2. Each CPU core selects a process according to the chosen scheduling policy
3. The process executes for one unit of burst time
4. Remaining burst time is updated
5. If a process finishes, waiting and turnaround metrics are recorded
6. Preemptive schedulers may return the process to the ready queue

---

# Multi-Core Simulation Model

The simulator models multiple CPU cores logically.

Each core is represented as a slot in a vector:

```cpp
std::vector<Process*> running(cores_);
```

Example if `cores = 4`:

```
running[0] → core 0
running[1] → core 1
running[2] → core 2
running[3] → core 3
```

At every simulated time step the scheduler iterates over all cores:

```cpp
for (int core = 0; core < cores_; ++core)
```

Each core:

* selects a process from the ready queue
* executes one time unit
* updates remaining burst time
* handles completion or preemption

This allows the simulator to model **multi-core scheduling behavior**.

Important:
The simulator itself runs as a **single program thread**. It simulates multiple CPU cores logically rather than using real OS threads. This keeps the simulation deterministic and avoids synchronization complexity.

---

# Metrics Collected

The simulator records classic scheduling metrics used in operating systems:

* Average Waiting Time
* Average Turnaround Time
* Number of Completed Processes

These metrics allow direct comparison between scheduling algorithms.

---

# Performance Profiling

The simulator can also be analyzed using Linux performance counters.

Example:

```
perf stat ./scheduler_sim
```

This reveals how the scheduling simulation translates into actual CPU behavior:

* instructions executed
* CPU cycles
* instruction per cycle (IPC)
* branch prediction accuracy

Example from a run with 1500 processes:

```
instructions: 1.45B
cycles:       686M
IPC:          2.12
branch miss:  0.11%
```

This connects **algorithm-level scheduling behavior** to **real hardware execution characteristics**.

---

# Build and Run

Compile:

```
g++ -std=c++17 main.cpp cpu/*.cpp metrics/*.cpp workload/*.cpp scheduler/*.cpp -o scheduler_sim
```

Run:

```
./scheduler_sim
```

Profile performance:

```
perf stat ./scheduler_sim
perf record ./scheduler_sim
perf report
```

---

# Design Goal

The purpose of this project is to build intuition about operating system scheduling policies and understand how algorithmic decisions interact with system-level performance.
