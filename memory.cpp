#include "memory.h"

Memory::Memory() {
    mem.resize(1024, 0);
L1D = new Cache(64, 16, 2, 1);
L1I = new Cache(64, 16, 2, 1);
L2  = new Cache(256, 16, 4, 5);
    memory_latency = 20;

    total_accesses = 0;
    total_misses = 0;
}

// LOAD
int Memory::load(int address, int &latency) {

    bool hitL1, hitL2;

    latency = 0;
    total_accesses++;

    latency += L1D->access(address, hitL1);

    if (!hitL1) {
        latency += L2->access(address, hitL2);

        if (!hitL2) {
            latency += memory_latency;
            total_misses++;
        }
    }

    return mem[address];
}

// STORE
int Memory::store(int address, int value, int &latency) {

    bool hitL1, hitL2;

    latency = 0;
    total_accesses++;

    latency += L1D->access(address, hitL1);

    if (!hitL1) {
        latency += L2->access(address, hitL2);

        if (!hitL2) {
            latency += memory_latency;
            total_misses++;
        }
    }

    mem[address] = value;

    return 0;
}

// INSTRUCTION FETCH
int Memory::fetch_instruction(int address, int &latency) {

    bool hitL1, hitL2;

    latency = 0;
    total_accesses++;

    latency += L1I->access(address, hitL1);

    if (!hitL1) {
        latency += L2->access(address, hitL2);

        if (!hitL2) {
            latency += memory_latency;
            total_misses++;
        }
    }

    return mem[address];
}