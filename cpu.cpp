#include "cpu.h"
#include "config.h"

#include <iostream>

extern Config config;

CPU::CPU() {

    pc = 0;

    reg.resize(32, 0);

    memory.mem[4096] = 10;
memory.mem[4100] = 20;
    memory.mem[5] = 10;
}



int CPU::accessData(int address) {

    bool hitL1, hitL2;

    int latency = 0;

   

    latency +=
        L1D.access(address, hitL1);

    if (!hitL1) {

        std::cout << "L1D MISS → ";

       

        latency +=
            L2.access(address, hitL2);

        if (!hitL2) {

            std::cout
                << "L2 MISS → MEMORY\n";

            latency += mem_latency;
        }

        else {

            std::cout
                << "L2 HIT\n";
        }
    }

    else {

        std::cout
            << "L1D HIT\n";
    }

    return latency;
}


int CPU::accessInstruction(int address) {

    bool hitL1, hitL2;

    int latency = 0;


    latency +=
        L1I.access(address, hitL1);

    if (!hitL1) {

        latency +=
            L2.access(address, hitL2);

        if (!hitL2) {

            latency += mem_latency;
        }
    }

    return latency;
}


void CPU::execute(Instruction instr) {

    int latency =
        config.getLatency(instr.opcode);

    std::cout
        << "Latency for "
        << instr.opcode
        << " = "
        << latency
        << std::endl;

   

    if (instr.opcode == "add") {

        reg[instr.rd] =
            reg[instr.rs1]
            +
            reg[instr.rs2];
    }

    else if (instr.opcode == "sub") {

        reg[instr.rd] =
            reg[instr.rs1]
            -
            reg[instr.rs2];
    }

    else if (instr.opcode == "mul") {

        reg[instr.rd] =
            reg[instr.rs1]
            *
            reg[instr.rs2];
    }

    else if (instr.opcode == "lw") {

        int addr =
            reg[instr.rs1]
            +
            instr.imm;

        int value =
            memory.mem[addr];

        reg[instr.rd] = value;
    }

    else if (instr.opcode == "sw") {

        int addr =
            reg[instr.rs1]
            +
            instr.imm;

        memory.mem[addr] =
            reg[instr.rs2];
    }


    else if (instr.opcode == "ADD") {

        reg[instr.rd] =
            reg[instr.rs1]
            +
            reg[instr.rs2];
    }

    else if (instr.opcode == "MUL") {

        reg[instr.rd] =
            reg[instr.rs1]
            *
            reg[instr.rs2];
    }

    else if (instr.opcode == "L") {

        int addr =
            instr.address;

        reg[instr.rd] =
            memory.mem[addr];
    }

    else if (instr.opcode == "S") {

        int addr =
            instr.address;

        memory.mem[addr] =
            reg[instr.rs1];
    }



    else if (instr.opcode == "bne") {

        if (
            reg[instr.rs1]
            !=
            reg[instr.rs2]
        ) {

            pc += instr.imm;
        }
    }

    else if (instr.opcode == "jal") {

        reg[instr.rd] = pc;

        pc += instr.imm;
    }

    std::cout
        << "Executing: "
        << instr.opcode
        << std::endl;
}



void CPU::printRegisters() {

    for (int i = 0; i < 8; i++) {

        std::cout
            << "x"
            << i
            << " = "
            << reg[i]
            << "\n";
    }
}