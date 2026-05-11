#include "instruction.h"

#include <sstream>
#include <iostream>

Instruction parseInstruction(std::string line) {

    std::stringstream ss(line);

    Instruction instr;

    std::string temp;

    instr.opcode = "";

    instr.rd = -1;
    instr.rs1 = -1;
    instr.rs2 = -1;

    instr.imm = 0;

    instr.address = 0;

    ss >> instr.opcode;

    // =====================================================
    // 🔥 PHASE 3 TRACE FORMAT
    // =====================================================

    // LOAD
    // Example:
    // L 0x1000 x5

    if (instr.opcode == "L") {

        std::string addr;
        std::string rd;

        ss >> addr >> rd;

        instr.address =
            std::stoul(addr, nullptr, 16);

        instr.rd =
            std::stoi(rd.substr(1));
    }

    // STORE
    // Example:
    // S 0x1004 x6

    else if (instr.opcode == "S") {

        std::string addr;
        std::string rs;

        ss >> addr >> rs;

        instr.address =
            std::stoul(addr, nullptr, 16);

        instr.rs1 =
            std::stoi(rs.substr(1));
    }

    // ADD / MUL
    // Example:
    // ADD x7 x5 x6
    // MUL x8 x7 x9

    else if (
        instr.opcode == "ADD" ||
        instr.opcode == "MUL"
    ) {

        std::string rd, rs1, rs2;

        ss >> rd >> rs1 >> rs2;

        instr.rd =
            std::stoi(rd.substr(1));

        instr.rs1 =
            std::stoi(rs1.substr(1));

        instr.rs2 =
            std::stoi(rs2.substr(1));
    }

    // =====================================================
    // 🔥 OLD PHASE 1 / 2 SUPPORT
    // =====================================================

    // add sub mul

    else if (
        instr.opcode == "add" ||
        instr.opcode == "sub" ||
        instr.opcode == "mul"
    ) {

        ss >> temp;
        instr.rd =
            std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs1 =
            std::stoi(temp.substr(1));

        ss >> temp;
        instr.rs2 =
            std::stoi(temp.substr(1));
    }

    // lw

    else if (instr.opcode == "lw") {

        std::string rd, addr;

        ss >> rd >> addr;

        instr.rd =
            std::stoi(rd.substr(1));

        // 0(x0)

        if (addr.find('(') != std::string::npos) {

            int pos1 = addr.find('(');
            int pos2 = addr.find(')');

            std::string imm_str =
                addr.substr(0, pos1);

            std::string reg_str =
                addr.substr(pos1 + 2,
                pos2 - pos1 - 2);

            instr.imm =
                std::stoi(imm_str);

            instr.rs1 =
                std::stoi(reg_str);
        }

        // 0 x0

        else {

            instr.imm =
                std::stoi(addr);

            ss >> temp;

            instr.rs1 =
                std::stoi(temp.substr(1));
        }
    }

    // sw

    else if (instr.opcode == "sw") {

        std::string rs2, addr;

        ss >> rs2 >> addr;

        instr.rs2 =
            std::stoi(rs2.substr(1));

        // 0(x0)

        if (addr.find('(') != std::string::npos) {

            int pos1 = addr.find('(');
            int pos2 = addr.find(')');

            std::string imm_str =
                addr.substr(0, pos1);

            std::string reg_str =
                addr.substr(pos1 + 2,
                pos2 - pos1 - 2);

            instr.imm =
                std::stoi(imm_str);

            instr.rs1 =
                std::stoi(reg_str);
        }

        // 0 x0

        else {

            instr.imm =
                std::stoi(addr);

            ss >> temp;

            instr.rs1 =
                std::stoi(temp.substr(1));
        }
    }

    // bne

    else if (instr.opcode == "bne") {

        ss >> temp;

        instr.rs1 =
            std::stoi(temp.substr(1));

        ss >> temp;

        instr.rs2 =
            std::stoi(temp.substr(1));

        ss >> instr.imm;
    }

    // jal

    else if (instr.opcode == "jal") {

        ss >> temp;

        instr.rd =
            std::stoi(temp.substr(1));

        ss >> instr.imm;
    }

    return instr;
}