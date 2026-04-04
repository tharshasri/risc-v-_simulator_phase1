#ifndef PIPELINE_H
#define PIPELINE_H

#include "instruction.h"
#include "memory.h"

struct Stage {
    Instruction instr;
    bool empty = true;
};

class Pipeline {

public:

    Stage IF, ID, EX, MEM, WB;

    int ex_cycles_remaining = 0;

    int stall_cycles = 0;   // NEW

    Memory *memory;         // NEW

    int pc = 0;             // NEW (for instruction fetch)

    void advance();
};

#endif