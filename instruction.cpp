#include "instruction.h"
#include <sstream>

Instruction parseInstruction(std::string line) {

    std::stringstream ss(line);
    Instruction instr;
    std::string temp;

    instr.opcode = "";
    instr.rd = -1;
    instr.rs1 = -1;
    instr.rs2 = -1;
    instr.imm = 0;

    ss >> instr.opcode;

    // 🔹 R-type
    if (instr.opcode == "add" || instr.opcode == "sub" || instr.opcode == "mul") {

        ss >> temp;
        instr.rd = std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs1 = std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs2 = std::stoi(temp.substr(1));
    }

    // 🔹 LOAD
    else if (instr.opcode == "lw") {

        std::string rd, addr;
        ss >> rd >> addr;

        instr.rd = std::stoi(rd.substr(1));

        // 🔥 CASE 1: format = 0(x0)
        if (addr.find('(') != std::string::npos) {

            int pos1 = addr.find('(');
            int pos2 = addr.find(')');

            std::string imm_str = addr.substr(0, pos1);
            std::string reg_str = addr.substr(pos1 + 2, pos2 - pos1 - 2);

            instr.imm = std::stoi(imm_str);
            instr.rs1 = std::stoi(reg_str);
        }
        // 🔥 CASE 2: format = 0 x0
        else {
            instr.imm = std::stoi(addr);

            ss >> temp;
            instr.rs1 = std::stoi(temp.substr(1));
        }
    }

    // 🔹 STORE
    else if (instr.opcode == "sw") {

        std::string rs2, addr;
        ss >> rs2 >> addr;

        instr.rs2 = std::stoi(rs2.substr(1));

        // 🔥 CASE 1: format = 0(x0)
        if (addr.find('(') != std::string::npos) {

            int pos1 = addr.find('(');
            int pos2 = addr.find(')');

            std::string imm_str = addr.substr(0, pos1);
            std::string reg_str = addr.substr(pos1 + 2, pos2 - pos1 - 2);

            instr.imm = std::stoi(imm_str);
            instr.rs1 = std::stoi(reg_str);
        }
        // 🔥 CASE 2: format = 0 x0
        else {
            instr.imm = std::stoi(addr);

            ss >> temp;
            instr.rs1 = std::stoi(temp.substr(1));
        }
    }

    // 🔹 BNE
    else if (instr.opcode == "bne") {

        ss >> temp;
        instr.rs1 = std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs2 = std::stoi(temp.substr(1));

        ss >> instr.imm;
    }

    // 🔹 JAL
    else if (instr.opcode == "jal") {

        ss >> temp;
        instr.rd = std::stoi(temp.substr(1));

        ss >> instr.imm;
    }

    return instr;
}