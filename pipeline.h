#ifndef PIPELINE_H
#define PIPELINE_H

#include "instruction.h"
#include "memory.h"
#include "cpu.h"  

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

   
    CPU *cpu;

    int pc = 0;

    void advance();
};

#endif