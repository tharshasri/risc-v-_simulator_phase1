#include "instruction.h"
#include <sstream>

Instruction parseInstruction(std::string line) {

    std::stringstream ss(line);
    Instruction instr;
    std::string temp;

<<<<<<< HEAD
   
=======
    
>>>>>>> 0007a5e61e9073c07bebc08e75a8e23e76a84be8
    instr.opcode = "";
    instr.rd = -1;
    instr.rs1 = -1;
    instr.rs2 = -1;
    instr.imm = 0;

    ss >> instr.opcode;

    if (instr.opcode == "add" || instr.opcode == "sub") {

        ss >> temp;
        instr.rd = std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs1 = std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs2 = std::stoi(temp.substr(1));
    }

    else if (instr.opcode == "lw") {

        ss >> temp;
        instr.rd = std::stoi(temp.substr(1));

        ss >> instr.imm;

        ss >> temp;
        instr.rs1 = std::stoi(temp.substr(1));
    }

    else if (instr.opcode == "sw") {

        ss >> temp;
        instr.rs2 = std::stoi(temp.substr(1));

        ss >> instr.imm;

        ss >> temp;
        instr.rs1 = std::stoi(temp.substr(1));
    }

    else if (instr.opcode == "bne") {

        ss >> temp;
        instr.rs1 = std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs2 = std::stoi(temp.substr(1));

        ss >> instr.imm;
    }

    else if (instr.opcode == "jal") {

        ss >> temp;
        instr.rd = std::stoi(temp.substr(1));

        ss >> instr.imm;
    }

    return instr;
}
