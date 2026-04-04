#include "cpu.h"
#include <iostream>

CPU::CPU() {
    pc = 0;
    reg.resize(32, 0);

    // Initialize some memory for testing
    memory.mem[5] = 10;
}

void CPU::execute(Instruction instr) {

    if (instr.opcode == "add") {
        reg[instr.rd] = reg[instr.rs1] + reg[instr.rs2];
    }

    else if (instr.opcode == "sub") {
        reg[instr.rd] = reg[instr.rs1] - reg[instr.rs2];
    }
    else if (instr.opcode == "mul") {
    reg[instr.rd] = reg[instr.rs1] * reg[instr.rs2];
}

    else if (instr.opcode == "lw") {
        int latency;
        int addr = reg[instr.rs1] + instr.imm;

        int value = memory.load(addr, latency);
        reg[instr.rd] = value;

        // NOTE: pipeline handles stalls, not CPU
    }

    else if (instr.opcode == "sw") {
        int latency;
        int addr = reg[instr.rs1] + instr.imm;

        memory.store(addr, reg[instr.rs2], latency);
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
    std::cout << "Executing: " << instr.opcode << std::endl;
}

void CPU::printRegisters() {
    for (int i = 0; i < 8; i++) {
        std::cout << "x" << i << " = " << reg[i] << "\n";
    }
}