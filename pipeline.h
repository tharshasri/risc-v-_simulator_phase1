#ifndef PIPELINE_H
#define PIPELINE_H

#include "instruction.h"

struct Stage {
    bool empty = true;
    Instruction instr;
};

class Pipeline {
public:
    Stage IF, ID, EX, MEM, WB;

    void advance();
};

#endif