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

    // 🔥 CONNECT CPU TO PIPELINE (IMPORTANT)
    pipe.cpu = &cpu;

    // Connect pipeline with memory (keep as is)
    pipe.memory = &cpu.memory;

    // 🔥 TAKE CACHE INPUTS
    int l1_size, l1_block, l1_assoc, l1_lat;
    int l2_size, l2_block, l2_assoc, l2_lat;
    int mem_lat;

    std::cout << "Enter L1 Cache (size block assoc latency): ";
    std::cin >> l1_size >> l1_block >> l1_assoc >> l1_lat;

    std::cout << "Enter L2 Cache (size block assoc latency): ";
    std::cin >> l2_size >> l2_block >> l2_assoc >> l2_lat;

    std::cout << "Enter Main Memory Latency: ";
    std::cin >> mem_lat;

    // 🔥 INITIALIZE CACHES
    cpu.L1I = Cache(l1_size, l1_block, l1_assoc, l1_lat);
    cpu.L1D = Cache(l1_size, l1_block, l1_assoc, l1_lat);
    cpu.L2  = Cache(l2_size, l2_block, l2_assoc, l2_lat);

    cpu.mem_latency = mem_lat;

    // 🔥🔥 VERY IMPORTANT FIX (CAUSE OF SEGFAULT)
    cpu.memory.L1D = &cpu.L1D;
    cpu.memory.L1I = &cpu.L1I;
    cpu.memory.L2  = &cpu.L2;
    cpu.memory.memory_latency = cpu.mem_latency;

    // Load config
    config.loadConfig("config.txt");

    std::vector<Instruction> program;

    std::ifstream file("program.asm");
    std::string line;

    while (getline(file, line)) {
        std::cout << "Reading line: [" << line << "]\n";
        if (line.empty()) continue;
        program.push_back(parseInstruction(line));
    }

    int cycles = 0;

    while (cpu.pc < program.size() ||
           !pipe.IF.empty || !pipe.ID.empty ||
           !pipe.EX.empty || !pipe.MEM.empty ||
           !pipe.WB.empty) {

        cycles++;

        bool stall = false;

        // 🔴 DATA HAZARD CHECK
        if (!pipe.ID.empty) {

            int rs1 = pipe.ID.instr.rs1;
            int rs2 = pipe.ID.instr.rs2;

            // EX hazard
            if (!pipe.EX.empty) {
                int rd = pipe.EX.instr.rd;

                if (rd != -1 && (rs1 == rd || rs2 == rd)) {

                    if (!forwarding) {
                        stall = true;
                    }
                    else {
                        // load-use hazard
                        if (pipe.EX.instr.opcode == "lw") {
                            stall = true;
                        }
                    }
                }
            }

            // MEM hazard
            if (!pipe.MEM.empty) {
                int rd = pipe.MEM.instr.rd;

                if (rd != -1 && (rs1 == rd || rs2 == rd)) {
                    if (!forwarding) {
                        stall = true;
                    }
                }
            }
        }

        // 🔴 PIPELINE CONTROL
        if (!stall) {
            pipe.advance();
        }
        else {
            pipe.WB = pipe.MEM;
            pipe.MEM = pipe.EX;
            pipe.EX.empty = true;

            pipe.stall_cycles++;
            std::cout << "STALL inserted\n";
        }

        // 🔴 EXECUTE WB
        if (!pipe.WB.empty) {
            cpu.execute(pipe.WB.instr);
            pipe.WB.empty = true;
        }

        // 🔴 HANDLE JAL
        if (!pipe.EX.empty && pipe.EX.instr.opcode == "jal") {

            cpu.reg[pipe.EX.instr.rd] = cpu.pc - 1;
            cpu.pc = (cpu.pc - 1) + pipe.EX.instr.imm;

            pipe.IF.empty = true;
            pipe.ID.empty = true;
        }

        // 🔴 FORWARDING
        if (forwarding && !pipe.EX.empty && !pipe.MEM.empty) {

            if (pipe.MEM.instr.rd != -1 &&
                pipe.MEM.instr.rd == pipe.EX.instr.rs1)
                cpu.reg[pipe.EX.instr.rs1] = cpu.reg[pipe.MEM.instr.rd];

            if (pipe.MEM.instr.rd != -1 &&
                pipe.MEM.instr.rd == pipe.EX.instr.rs2)
                cpu.reg[pipe.EX.instr.rs2] = cpu.reg[pipe.MEM.instr.rd];
        }

        // 🔴 FETCH (🔥 UPDATED WITH CACHE)
        if (pipe.IF.empty && cpu.pc < program.size()) {

            int fetch_latency = cpu.accessInstruction(cpu.pc);

           // pipe.stall_cycles += (fetch_latency - 1);

            pipe.IF.instr = program[cpu.pc];
            pipe.IF.empty = false;
            cpu.pc++;
        }
    }

    // 🔴 OUTPUT
    cpu.printRegisters();

    std::cout << "Total Cycles: " << cycles << "\n";
    std::cout << "Total Stalls: " << pipe.stall_cycles << "\n";

    double ipc = (double)program.size() / cycles;
    std::cout << "IPC: " << ipc << "\n";

    double total_accesses = cpu.L1D.total_accesses + cpu.L1I.total_accesses;
double total_misses   = cpu.L1D.total_misses + cpu.L1I.total_misses;

double miss_rate = (double)total_misses / total_accesses;
    std::cout << "Cache Miss Rate: " << miss_rate << "\n";

    return 0;
}