#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include <vector>
#include "instruction.h"
#include "cache.h"

class CPU {
public:
    int pc;
    std::vector<int> reg;
    Memory memory;

    // 🔥 Caches
    Cache L1I;
    Cache L1D;
    Cache L2;

    int mem_latency;

    CPU();

    void execute(Instruction instr);
    void printRegisters();

    // 🔥 ADD THESE (fixes compile error)
    int accessData(int address);
    int accessInstruction(int address);
};

#endif