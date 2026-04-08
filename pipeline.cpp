#include "pipeline.h"
#include "config.h"
#include "cpu.h"
#include <iostream>

extern Config config;
extern CPU cpu;

void Pipeline::advance() {

    // 🔴 HANDLE MULTI-CYCLE EXECUTION (CACHE LATENCY)

    if (!EX.empty) {

        if (ex_cycles_remaining > 1) {
            ex_cycles_remaining--;

            // ❌ REMOVED: stall_cycles++ (this was causing overcount)

            return;  // stall pipeline
        }
    }

    // 🔴 MOVE PIPELINE FORWARD

    WB = MEM;
    MEM = EX;
    EX = ID;
    ID = IF;

    IF.empty = true;

    // 🔴 SET LATENCY FOR INSTRUCTION ENTERING EX

    if (!EX.empty) {

        int lat = 1;  // default for ALU instructions

        // 🔥 HANDLE LOAD / STORE (DATA CACHE)
        if (EX.instr.opcode == "lw" || EX.instr.opcode == "sw") {

            int address = EX.instr.imm;

            int temp;
            memory->load(address, temp);
            lat = temp;

            std::cout << "[DATA ACCESS] ";
        }

        else {
            lat = 1;
        }

        std::cout << "Latency for " << EX.instr.opcode
                  << " = " << lat << std::endl;

        ex_cycles_remaining = lat;

        // 🔥 ADD STALLS ONLY HERE (CORRECT PLACE)
        if (lat > 1) {
            stall_cycles += (lat - 1);
        }
    }
}