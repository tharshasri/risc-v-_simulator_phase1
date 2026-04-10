# RISC-V Pipeline Simulator (C++)

## Project Overview

This project implements a **RISC-V Pipeline Simulator** using C++.
The simulator models a **5-stage pipeline processor** and demonstrates how instructions move through pipeline stages while handling **data hazards, stalls, and forwarding**.

The project helps understand important computer architecture concepts such as:

* Instruction pipelining
* Data hazards
* Stall insertion
* Forwarding mechanisms
* Pipeline performance metrics

The simulator reads a **RISC-V assembly program**, executes it using the pipeline model, and displays the **final register values and performance statistics** such as cycles, stalls, and IPC.

---

# Development Process

Since this project was developed individually, development was done in multiple phases including design, implementation, testing, and debugging.

---

# Phase 1 – Project Planning

**Date:** March 1, 2026
**Mode:** Individual planning

### Objectives

The goal of the project was to build a simulator that demonstrates how a RISC-V processor pipeline works.

### Tools Selected

* **Programming Language:** C++
* **Editor:** Visual Studio Code
* **Compiler:** g++
* **Platform:** WSL (Ubuntu)
* **Version Control:** Git & GitHub

### Planned Modules

The simulator was divided into multiple components to simplify development:

1. Instruction parsing
2. CPU execution logic
3. Memory model
4. Pipeline structure
5. Hazard detection
6. Forwarding mechanism
7. Performance metrics

---

# Phase 2 – Implementation

**Date:** March 6, 2026

During this phase, the core components of the simulator were implemented.

### Implemented Components

**Instruction Parser**

Parses RISC-V assembly instructions and converts them into internal instruction structures.

**CPU Module**

Responsible for executing instructions such as:

* ADD
* SUB
* LW
* SW
* BNE
* JAL

**Memory Model**

Simulates memory operations for load and store instructions.

**Pipeline Module**

Implements the **5-stage pipeline**:

1. Instruction Fetch (IF)
2. Instruction Decode (ID)
3. Execute (EX)
4. Memory (MEM)
5. Write Back (WB)

Pipeline registers are used between stages to simulate instruction flow.

---

# Phase 3 – Hazard Detection and Forwarding

**Date:** March 7, 2026

The next step was implementing **data hazard detection** and **pipeline stalls**.

### Hazard Handling

The simulator detects **data dependencies** between instructions.

When forwarding is disabled:

* The simulator inserts **stalls** when dependencies occur.

When forwarding is enabled:

* Values are forwarded from later pipeline stages to reduce stalls.

---

# Phase 4 – Testing and Debugging (march 8 from afternoon 4 onwards)

The simulator was tested using sample RISC-V assembly programs.

Example test program:


lw x1 5 x0
add x2 x1 x1
add x3 x2 x1
add x4 x3 x1


The simulator outputs:

* Register values
* Total cycles
* Number of stalls
* Instructions per cycle (IPC)



# Use of AI Assistance

During development, **AI tools were used as a programming assistant** to support the project in the following ways:

* Understanding RISC-V pipeline concepts
* Debugging C++ compilation issues
* Improving hazard detection logic
* Fixing pipeline stall handling
* Clarifying instruction parsing logic
* Improving code structure and documentation

The final implementation and integration of all modules were performed manually.

AI was mainly used for:

* Guidance
* Code explanations
* Debugging suggestions



# Project Structure


riscv_sim/
│
├── main.cpp          # Main driver program for simulator
├── cpu.cpp           # CPU execution logic
├── cpu.h
│
├── instruction.cpp   # Instruction parser
├── instruction.h
│
├── memory.cpp        # Memory model
├── memory.h
│
├── pipeline.cpp      # Pipeline stage logic
├── pipeline.h
│
├── program.asm       # Sample assembly program
│
├── Makefile          # Build configuration
│
└── README.md         # Project documentation



# How to Compile and Run

### Step 1 – Open terminal

Navigate to the project folder.


cd riscv_sim


### Step 2 – Compile the simulator

g++ main.cpp cpu.cpp instruction.cpp memory.cpp pipeline.cpp -o sim


### Step 3 – Run the simulator


./sim


### Step 4 – Select forwarding mode


Enable forwarding? (1=yes, 0=no)




# Example Output


Enable forwarding? (1=yes, 0=no): 0

STALL inserted
STALL inserted
STALL inserted

x0 = 0
x1 = 10
x2 = 20
x3 = 30
x4 = 40

Total Cycles: 11
Total Stalls: 3
IPC: 0.36




# Learning Outcomes

Through this project, the following concepts were learned:

* RISC-V instruction execution
* Pipeline architecture
* Data hazards and stall logic
* Forwarding mechanisms
* Performance evaluation using IPC



# Future Improvements

Possible future enhancements include:

* Support for more RISC-V instructions
* Branch prediction
* Variable latency memory
* Pipeline visualization
* Support for larger test programs




# what are not working in this project for now 
 * the latency is not working properly 
 * the large codes like bubble sort are not working properly 
 * mul is also not working .

# Author

**Name:** Tharsha Sri
**Program:** Computer Science Engineering
**Project:** RISC-V Pipeline Simulator
# RISC-V Pipeline Simulator with Cache (C++)

## 📌 Project Overview

This project implements a **RISC-V Pipeline Simulator** using C++. It models a **5-stage pipelined processor** along with a **multi-level cache hierarchy (L1 Instruction Cache, L1 Data Cache, and L2 Unified Cache)**.

The simulator demonstrates how instructions move through pipeline stages while handling:

- Instruction pipelining  
- Data hazards  
- Stall insertion  
- Forwarding mechanisms  
- Cache memory behavior  
- Variable latency execution  
- Performance metrics  

The simulator takes:

- **Instruction input from `program.asm`**
- **Cache configuration and instruction latencies from `config.txt`**

and produces:

- Final register values  
- Total cycles  
- Total stalls  
- IPC (Instructions per Cycle)  
- Cache miss rate  

---

## 🧠 Key Concepts Covered

- 5-stage pipeline architecture (IF, ID, EX, MEM, WB)  
- Data hazard detection and resolution  
- Forwarding vs non-forwarding execution  
- Multi-level cache hierarchy  
- Variable latency memory access  
- Performance evaluation using IPC and miss rate  

---

## 🛠️ Development Phases

### 🔹 Phase 1 – Planning  
**Date:** March 1, 2026  

- Designed overall architecture  
- Identified core modules:
  - Instruction parser  
  - CPU execution  
  - Memory system  
  - Pipeline stages  
  - Hazard detection  
  - Performance metrics  

### 🔹 Phase 2 – Core Implementation  
**Date:** March 6, 2026  

Implemented:

- Instruction parser for RISC-V assembly  
- CPU execution logic  
- Memory model  
- 5-stage pipeline simulation  

### 🔹 Phase 3 – Hazard Detection & Forwarding  
**Date:** March 7, 2026  

- Implemented data hazard detection  
- Inserted stalls when forwarding is disabled  
- Enabled forwarding to reduce stalls  

### 🔹 Phase 4 – Cache Integration (Phase 2 Extension)

- Added **L1I, L1D, and L2 caches**
- Implemented **LRU replacement policy**
- Introduced **variable latency memory access**
- Integrated cache with pipeline execution  

---

## 📂 Project Structure

riscv_sim/
│
├── main.cpp              # Main driver program  
├── cpu.cpp / cpu.h       # CPU execution logic  
├── instruction.cpp/.h    # Instruction parser  
├── memory.cpp/.h         # Memory + cache integration  
├── pipeline.cpp/.h       # Pipeline stage logic  
├── cache.cpp/.h          # Cache implementation (LRU)  
├── config.cpp/.h         # Instruction latency loader  
│  
├── program.asm           # Input RISC-V instructions  
├── config.txt            # Cache config + instruction latencies  
│  
└── README.md             # Project documentation  

---

## ⚙️ Input Files

### 📌 program.asm
Contains RISC-V assembly instructions to execute.

Example:
lw x1 0(x0)  
lw x2 0(x0)  
lw x3 0(x0)  
add x4 x1 x2  
lw x5 4(x0)  
lw x6 4(x0)  

---

### 📌 config.txt
Contains cache configuration and instruction latencies.

Example:
64 4 2 1  
128 4 2 5  
20  

lw 2  
sw 2  
add 1  
mul 3  
sub 1  
bne 1  
jal 1  

---

### 🔍 Explanation

- Line 1 → L1 Cache (size, block size, associativity, latency)  
- Line 2 → L2 Cache  
- Line 3 → Main memory latency  
- Remaining lines → Instruction latencies  

---

## ▶️ How to Compile and Run

Step 1 – Navigate to project folder  
cd riscv_sim  

Step 2 – Compile  
g++ main.cpp cpu.cpp instruction.cpp memory.cpp pipeline.cpp cache.cpp config.cpp -o sim  

Step 3 – Run  
./sim  

Step 4 – Input  
Enable forwarding? (1=yes, 0=no): 1  

---

## 📊 Example Output

CACHE MISS (Address: 0)  
CACHE HIT (Address: 0)  

Total Cycles: 20  
Total Stalls: 8  
IPC: 0.3  
Cache Miss Rate: 0.36  

---

## 🎯 Learning Outcomes

- Understanding pipelined execution  
- Handling hazards and stalls  
- Cache memory hierarchy  
- Variable latency modeling  
- Performance evaluation  

---

## ⚠️ Current Limitations

- MUL instruction may not work correctly in all cases  
- Large programs may not execute fully  
- Latency modeling can be improved  
- No branch prediction  

---

## 🚀 Future Improvements

- Branch prediction  
- Additional cache policies (FIFO, Random)  
- Pipeline visualization  
- Support for larger programs  
- GUI-based simulator  

---

## 🤖 Use of AI Assistance

AI tools were used for:

- Understanding pipeline concepts  
- Debugging C++ errors  
- Improving cache integration  
- Fixing stall logic  

Final implementation and integration were done manually.

---

## 👨‍💻 Author

Name: Tharsha Sri  
Program: Computer Science Engineering  
Project: RISC-V Pipeline Simulator with Cache