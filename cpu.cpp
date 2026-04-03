#include "cpu.h"
#include <iostream>

CPU::CPU() {
    pc = 0;
    reg.resize(32, 0);

<<<<<<< HEAD
=======
    
>>>>>>> 0007a5e61e9073c07bebc08e75a8e23e76a84be8
    memory.mem[5] = 10;
}

void CPU::execute(Instruction instr) {

    if (instr.opcode == "add") {
        reg[instr.rd] = reg[instr.rs1] + reg[instr.rs2];
    }

    else if (instr.opcode == "sub") {
        reg[instr.rd] = reg[instr.rs1] - reg[instr.rs2];
    }

    else if (instr.opcode == "lw") {
        reg[instr.rd] = memory.load(reg[instr.rs1] + instr.imm);
    }

    else if (instr.opcode == "sw") {
        memory.store(reg[instr.rs1] + instr.imm, reg[instr.rs2]);
    }

    else if (instr.opcode == "bne") {
        if (reg[instr.rs1] != reg[instr.rs2]) {
            pc += instr.imm;
        }
    }

    else if (instr.opcode == "jal") {
        reg[instr.rd] = pc;
        pc += instr.imm;
    }
}

void CPU::printRegisters() {
    for (int i = 0; i < 8; i++) {
        std::cout << "x" << i << " = " << reg[i] << "\n";
    }
}
