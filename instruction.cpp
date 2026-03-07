#include "instruction.h"
#include <sstream>

Instruction parseInstruction(std::string line) {
    std::stringstream ss(line);
    Instruction instr;
    std::string temp;

    ss >> instr.opcode;

    if (instr.opcode == "add" || instr.opcode == "sub") {
        ss >> temp; instr.rd = std::stoi(temp.substr(1));
        ss >> temp; instr.rs1 = std::stoi(temp.substr(1));
        ss >> temp; instr.rs2 = std::stoi(temp.substr(1));
    }

    else if (instr.opcode == "lw") {
        ss >> temp; instr.rd = std::stoi(temp.substr(1));
        ss >> instr.imm;
        ss >> temp; instr.rs1 = std::stoi(temp.substr(1));
    }

    else if (instr.opcode == "sw") {
        ss >> temp; instr.rs2 = std::stoi(temp.substr(1));
        ss >> instr.imm;
        ss >> temp; instr.rs1 = std::stoi(temp.substr(1));
    }

    else if (instr.opcode == "bne") {
        ss >> temp; instr.rs1 = std::stoi(temp.substr(1));
        ss >> temp; instr.rs2 = std::stoi(temp.substr(1));
        ss >> instr.imm;
    }

    else if (instr.opcode == "jal") {
        ss >> temp;
        instr.rd = std::stoi(temp.substr(1));
        ss >> instr.imm;
    }

    return instr;
}