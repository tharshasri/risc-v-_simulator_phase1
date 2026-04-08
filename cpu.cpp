#include "cpu.h"
#include <iostream>

CPU::CPU() {
    pc = 0;
    reg.resize(32, 0);

    // Initialize some memory for testing
    memory.mem[5] = 10;
}

// 🔥 NEW: DATA CACHE ACCESS
int CPU::accessData(int address) {

    bool hitL1, hitL2;
    int latency = 0;

    // L1D access
    latency += L1D.access(address, hitL1);

    if (!hitL1) {
        std::cout << "L1D MISS → ";

        // L2 access
        latency += L2.access(address, hitL2);

        if (!hitL2) {
            std::cout << "L2 MISS → MEMORY\n";
            latency += mem_latency;
        } else {
            std::cout << "L2 HIT\n";
        }
    } else {
        std::cout << "L1D HIT\n";
    }

    return latency;
}

// 🔥 NEW: INSTRUCTION CACHE ACCESS
int CPU::accessInstruction(int address) {

    bool hitL1, hitL2;
    int latency = 0;

    // L1I access
    latency += L1I.access(address, hitL1);

    if (!hitL1) {

        latency += L2.access(address, hitL2);

        if (!hitL2) {
            latency += mem_latency;
        }
    }

    return latency;
}

// 🔥 EXECUTION (KEEP MOSTLY SAME)
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

        int addr = reg[instr.rs1] + instr.imm;

        // 🔥 ONLY FETCH VALUE (latency handled in pipeline)
        int value = memory.mem[addr];

        reg[instr.rd] = value;
    }

    else if (instr.opcode == "sw") {

        int addr = reg[instr.rs1] + instr.imm;

        // 🔥 STORE DIRECTLY (latency handled in pipeline)
        memory.mem[addr] = reg[instr.rs2];
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