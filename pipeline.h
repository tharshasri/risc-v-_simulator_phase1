#ifndef PIPELINE_H
#define PIPELINE_H

#include "instruction.h"
#include "memory.h"
#include "cpu.h"   // 🔥 ADD THIS

struct Stage {
    Instruction instr;
    bool empty = true;
};

class Pipeline {

public:

    Stage IF, ID, EX, MEM, WB;

    int ex_cycles_remaining = 0;
    int stall_cycles = 0;

    Memory *memory;

    // 🔥 ADD THIS (fix error)
    CPU *cpu;

    int pc = 0;

    void advance();
};

#endif