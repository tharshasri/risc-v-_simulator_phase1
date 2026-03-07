#include <iostream>
#include <fstream>
#include <vector>
#include "cpu.h"
#include "pipeline.h"

int main() {

    CPU cpu;
    Pipeline pipe;

    std::vector<Instruction> program;

    std::ifstream file("program.asm");
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        program.push_back(parseInstruction(line));
    }

    int cycles = 0;

    while (cpu.pc < program.size() || !pipe.IF.empty || !pipe.ID.empty || !pipe.EX.empty || !pipe.MEM.empty || !pipe.WB.empty) {

        cycles++;

        pipe.advance();

       if (!pipe.WB.empty) {

    int old_pc = cpu.pc;
    cpu.execute(pipe.WB.instr);

    if (cpu.pc != old_pc + 1) {   // jump happened
        pipe.IF.empty = true;
        pipe.ID.empty = true;
    }
}
if (!pipe.EX.empty) {

    if (pipe.EX.instr.opcode == "jal") {

        // save return address
        cpu.reg[pipe.EX.instr.rd] = cpu.pc - 1;

        // compute jump target
        cpu.pc = (cpu.pc - 1) + pipe.EX.instr.imm;

        // flush wrong instructions
        pipe.IF.empty = true;
        pipe.ID.empty = true;
        pipe.EX.empty = true;

    }
}
        if (pipe.IF.empty && cpu.pc < program.size()) {
    pipe.IF.instr = program[cpu.pc];
    pipe.IF.empty = false;
    cpu.pc++;
}
    }

    cpu.printRegisters();

    std::cout << "Total Cycles: " << cycles << "\n";

    return 0;
}