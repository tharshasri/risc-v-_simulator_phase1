#ifndef PIPELINE_H
#define PIPELINE_H

#include "instruction.h"

struct Stage {
    Instruction instr;
    bool empty = true;
};

class Pipeline {

public:

    Stage IF, ID, EX, MEM, WB;

    int ex_cycles_remaining = 0;   // ADD THIS LINE

    void advance();
};

#endif