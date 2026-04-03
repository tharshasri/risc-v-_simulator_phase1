#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "cpu.h"
#include "pipeline.h"

#include "config.h"   
Config config;
int main() {

    bool forwarding;

    std::cout << "Enable forwarding? (1=yes, 0=no): ";
    std::cin >> forwarding;

    CPU cpu;
    Pipeline pipe;

                 
    config.loadConfig("config.txt");   

    std::vector<Instruction> program;

    std::ifstream file("program.asm");
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        program.push_back(parseInstruction(line));
    }

    int cycles = 0;
    int stalls = 0;

    while (cpu.pc < program.size() ||
           !pipe.IF.empty || !pipe.ID.empty ||
           !pipe.EX.empty || !pipe.MEM.empty ||
           !pipe.WB.empty) {

        cycles++;

        bool stall = false;

        if (!pipe.ID.empty) {

            int rs1 = pipe.ID.instr.rs1;
            int rs2 = pipe.ID.instr.rs2;

          
            if (!pipe.EX.empty) {

                int rd = pipe.EX.instr.rd;

                if (rd != -1 && (rs1 == rd || rs2 == rd)) {
                    if (!forwarding)
                        stall = true;
                }
            }

           
            if (!pipe.MEM.empty) {

                int rd = pipe.MEM.instr.rd;

                if (rd != -1 && (rs1 == rd || rs2 == rd)) {
                    if (!forwarding)
                        stall = true;
                }
            }
        }

    
        if (!stall) {
            pipe.advance();
        }
        else {

          
            pipe.WB = pipe.MEM;
            pipe.MEM = pipe.EX;
            pipe.EX.empty = true;

          

            stalls++;

            std::cout << "STALL inserted\n";
        }

       
        if (!pipe.WB.empty) {
            cpu.execute(pipe.WB.instr);
        }

     
        if (!pipe.EX.empty) {

            if (pipe.EX.instr.opcode == "jal") {

                cpu.reg[pipe.EX.instr.rd] = cpu.pc - 1;
                cpu.pc = (cpu.pc - 1) + pipe.EX.instr.imm;

                pipe.IF.empty = true;
                pipe.ID.empty = true;
            }
        }

       
        if (forwarding && !pipe.EX.empty && !pipe.MEM.empty) {

            if (pipe.MEM.instr.rd == pipe.EX.instr.rs1)
                cpu.reg[pipe.EX.instr.rs1] = cpu.reg[pipe.MEM.instr.rd];

            if (pipe.MEM.instr.rd == pipe.EX.instr.rs2)
                cpu.reg[pipe.EX.instr.rs2] = cpu.reg[pipe.MEM.instr.rd];
        }

        if (pipe.IF.empty && cpu.pc < program.size()) {

            pipe.IF.instr = program[cpu.pc];
            pipe.IF.empty = false;
            cpu.pc++;
        }
    }

    cpu.printRegisters();

    std::cout << "Total Cycles: " << cycles << "\n";
    std::cout << "Total Stalls: " << stalls << "\n";

    double ipc = (double)program.size() / cycles;
    std::cout << "IPC: " << ipc << "\n";

    return 0;
}