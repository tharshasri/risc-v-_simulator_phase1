#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

struct Instruction {
    std::string opcode;
    int rd = -1;
    int rs1 = -1;
    int rs2 = -1;
     int imm = 0;
};

Instruction parseInstruction(std::string line);

#endif