#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "cpu.h"
#include "pipeline.h"
#include "config.h"
#include "vm.h"

Config config;

int main() {

    bool forwarding;

    
    std::cout << "Enable forwarding? (1=yes, 0=no): ";
    std::cin >> forwarding;

    CPU cpu;
    Pipeline pipe;

  
    pipe.cpu = &cpu;

    pipe.memory = &cpu.memory;

 

    config.loadConfig("config.txt");

 

    int l1_size, l1_block, l1_assoc, l1_lat;
    int l2_size, l2_block, l2_assoc, l2_lat;
    int mem_lat;

    std::ifstream inputFile("config.txt");

    if (!inputFile) {

        std::cout << "Error opening input file\n";
        return 1;
    }

    inputFile >> l1_size
              >> l1_block
              >> l1_assoc
              >> l1_lat;

    inputFile >> l2_size
              >> l2_block
              >> l2_assoc
              >> l2_lat;

    inputFile >> mem_lat;

   

    cpu.L1I =
        Cache(l1_size,
              l1_block,
              l1_assoc,
              l1_lat);

    cpu.L1D =
        Cache(l1_size,
              l1_block,
              l1_assoc,
              l1_lat);

    cpu.L2 =
        Cache(l2_size,
              l2_block,
              l2_assoc,
              l2_lat);

    cpu.mem_latency = mem_lat;


    cpu.memory.L1D = &cpu.L1D;
    cpu.memory.L1I = &cpu.L1I;
    cpu.memory.L2  = &cpu.L2;

    cpu.memory.memory_latency =
        cpu.mem_latency;


    VirtualMemory vm(

        config.virtualSize,

        config.physicalSize,

        config.pageSize,

        config.dtlbEntries,

        config.tlbHitLatency,

        config.pageWalkLatency,

        config.pageFaultLatency,

        config.replacementPolicy
    );

   

    std::vector<Instruction> program;

    std::ifstream file("trace.txt");

    if (!file) {

        std::cout << "Error opening trace.txt\n";
        return 1;
    }

    std::string line;

    while (getline(file, line)) {

        std::cout
            << "Reading line: ["
            << line
            << "]\n";

        if (line.empty())
            continue;

        Instruction instr =
            parseInstruction(line);


        if (instr.opcode == "L") {

            vm.translateAddress(
                instr.address,
                false
            );
        }

        else if (instr.opcode == "S") {

            vm.translateAddress(
                instr.address,
                true
            );
        }

        program.push_back(instr);
    }

   

    int cycles = 0;

    while (

        cpu.pc < program.size()

        ||

        !pipe.IF.empty
        ||

        !pipe.ID.empty
        ||

        !pipe.EX.empty
        ||

        !pipe.MEM.empty
        ||

        !pipe.WB.empty
    ) {

        cycles++;

        bool stall = false;

      

        if (!pipe.ID.empty) {

            int rs1 =
                pipe.ID.instr.rs1;

            int rs2 =
                pipe.ID.instr.rs2;

         

            if (!pipe.EX.empty) {

                int rd =
                    pipe.EX.instr.rd;

                if (
                    rd != -1
                    &&
                    (
                        rs1 == rd
                        ||
                        rs2 == rd
                    )
                ) {

                    if (!forwarding) {

                        stall = true;
                    }

                    else {

                      

                        if (
                            pipe.EX.instr.opcode == "lw"
                            ||
                            pipe.EX.instr.opcode == "L"
                        ) {

                            stall = true;
                        }
                    }
                }
            }

       

            if (!pipe.MEM.empty) {

                int rd =
                    pipe.MEM.instr.rd;

                if (
                    rd != -1
                    &&
                    (
                        rs1 == rd
                        ||
                        rs2 == rd
                    )
                ) {

                    if (!forwarding) {

                        stall = true;
                    }
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

            pipe.stall_cycles++;

            std::cout
                << "STALL inserted\n";
        }


        if (!pipe.WB.empty) {

            cpu.execute(
                pipe.WB.instr
            );

            pipe.WB.empty = true;
        }


        if (
            !pipe.EX.empty
            &&
            pipe.EX.instr.opcode == "jal"
        ) {

            cpu.reg[
                pipe.EX.instr.rd
            ] = cpu.pc - 1;

            cpu.pc =
                (cpu.pc - 1)
                +
                pipe.EX.instr.imm;

            pipe.IF.empty = true;

            pipe.ID.empty = true;
        }

      

        if (
            forwarding
            &&
            !pipe.EX.empty
            &&
            !pipe.MEM.empty
        ) {

            if (

                pipe.MEM.instr.rd != -1

                &&

                pipe.MEM.instr.rd
                ==
                pipe.EX.instr.rs1
            ) {

                cpu.reg[
                    pipe.EX.instr.rs1
                ]
                =
                cpu.reg[
                    pipe.MEM.instr.rd
                ];
            }

            if (

                pipe.MEM.instr.rd != -1

                &&

                pipe.MEM.instr.rd
                ==
                pipe.EX.instr.rs2
            ) {

                cpu.reg[
                    pipe.EX.instr.rs2
                ]
                =
                cpu.reg[
                    pipe.MEM.instr.rd
                ];
            }
        }

    

        if (

            pipe.IF.empty

            &&

            cpu.pc < program.size()
        ) {

            int fetch_latency =
                cpu.accessInstruction(
                    cpu.pc
                );

            pipe.IF.instr =
                program[cpu.pc];

            pipe.IF.empty = false;

            cpu.pc++;
        }
    }


    cycles += vm.translationCycles;


    cpu.printRegisters();

    std::cout
        << "Total Cycles: "
        << cycles
        << "\n";

    std::cout
        << "Total Stalls: "
        << pipe.stall_cycles
        << "\n";

    double ipc =
        (double)program.size()
        /
        cycles;

    std::cout
        << "IPC: "
        << ipc
        << "\n";

    double total_accesses =

        cpu.L1D.total_accesses

        +

        cpu.L1I.total_accesses;

    double total_misses =

        cpu.L1D.total_misses

        +

        cpu.L1I.total_misses;

    double miss_rate =

        (double)total_misses
        /
        total_accesses;

    std::cout
        << "Cache Miss Rate: "
        << miss_rate
        << "\n";


    std::cout
        << "\n===== VM Statistics =====\n";

    std::cout
        << "TLB Hits: "
        << vm.tlbHits
        << "\n";

    std::cout
        << "TLB Misses: "
        << vm.tlbMisses
        << "\n";

    std::cout
        << "Page Walks: "
        << vm.pageWalks
        << "\n";

    std::cout
        << "Page Faults: "
        << vm.pageFaults
        << "\n";

    std::cout
        << "Page Evictions: "
        << vm.evictions
        << "\n";

    std::cout
        << "Dirty Evictions: "
        << vm.dirtyEvictions
        << "\n";

    std::cout
        << "Translation Penalty Cycles: "
        << vm.translationCycles
        << "\n";

    return 0;
}