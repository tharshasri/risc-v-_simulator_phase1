#include "pipeline.h"
#include "config.h"
#include <iostream>

extern Config config;

void Pipeline::advance() {

    // 🔴 EX latency
    if (!EX.empty) {

        if (ex_cycles_remaining > 1) {
            ex_cycles_remaining--;
            stall_cycles++;
            return;
        }
    }

    // 🔴 MOVE PIPELINE
    WB = MEM;
    MEM = EX;
    EX = ID;
    ID = IF;

    IF.empty = true;

    // 🔴 SET EX LATENCY
    if (!EX.empty) {

        int lat = config.getLatency(EX.instr.opcode);

        std::cout << "Latency for " << EX.instr.opcode
                  << " = " << lat << std::endl;

        ex_cycles_remaining = lat;
    }
}