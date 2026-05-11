#include "memory.h"

#include <iostream>

Memory::Memory() {

    mem.resize(1024 * 1024, 0);

    L1D = nullptr;
    L1I = nullptr;
    L2  = nullptr;

    memory_latency = 20;

    total_accesses = 0;
    total_misses   = 0;
}



int Memory::load(int address, int &latency) {

    bool hitL1 = false;
    bool hitL2 = false;

    latency = 0;

    total_accesses++;

   

    if (address < 0 || address >= mem.size()) {

        std::cout
            << "Memory load out of bounds: "
            << address
            << "\n";

        return 0;
    }

 

    if (L1D != nullptr) {

        latency +=
            L1D->access(address, hitL1);
    }



    if (!hitL1 && L2 != nullptr) {

        latency +=
            L2->access(address, hitL2);

      

        if (!hitL2) {

            latency += memory_latency;

            total_misses++;
        }
    }

    return mem[address];
}


int Memory::store(
    int address,
    int value,
    int &latency
) {

    bool hitL1 = false;
    bool hitL2 = false;

    latency = 0;

    total_accesses++;


    if (address < 0 || address >= mem.size()) {

        std::cout
            << "Memory store out of bounds: "
            << address
            << "\n";

        return 0;
    }

 

    if (L1D != nullptr) {

        latency +=
            L1D->access(address, hitL1);
    }

  

    if (!hitL1 && L2 != nullptr) {

        latency +=
            L2->access(address, hitL2);


        if (!hitL2) {

            latency += memory_latency;

            total_misses++;
        }
    }

    // 🔥 STORE VALUE

    mem[address] = value;

    return 0;
}



int Memory::fetch_instruction(
    int address,
    int &latency
) {

    bool hitL1 = false;
    bool hitL2 = false;

    latency = 0;

    total_accesses++;


    if (address < 0 || address >= mem.size()) {

        std::cout
            << "Instruction fetch out of bounds: "
            << address
            << "\n";

        return 0;
    }

  

    if (L1I != nullptr) {

        latency +=
            L1I->access(address, hitL1);
    }

    if (!hitL1 && L2 != nullptr) {

        latency +=
            L2->access(address, hitL2);

    

        if (!hitL2) {

            latency += memory_latency;

            total_misses++;
        }
    }

    return mem[address];
}