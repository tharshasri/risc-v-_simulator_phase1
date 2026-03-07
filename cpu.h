#ifndef CPU_H
#define CPU_H
#include "memory.h"

#include <vector>
#include "instruction.h"

class CPU {
public:
    int pc;
    std::vector<int> reg;
    
    Memory memory;
    

    CPU();
    void execute(Instruction instr);
    void printRegisters();
};

#endif