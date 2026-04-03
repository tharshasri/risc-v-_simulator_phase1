#include "pipeline.h"
#include "config.h"
#include <iostream>   // ADD THIS LINE

extern Config config;

void Pipeline::advance() {

    // If EX stage instruction still needs cycles
    if (!EX.empty) {

        if (ex_cycles_remaining > 1) {
            ex_cycles_remaining--;
            return;
        }
    }

    // Move pipeline
    WB = MEM;
    MEM = EX;
    EX = ID;
    ID = IF;

    IF.empty = true;

    // Load latency for instruction entering EX
    if (!EX.empty) {

        int lat = config.getLatency(EX.instr.opcode);

        std::cout << "Latency for " << EX.instr.opcode
                  << " = " << lat << std::endl;

        ex_cycles_remaining = lat;
    }
}