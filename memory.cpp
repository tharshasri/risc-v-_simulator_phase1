#include "memory.h"

Memory::Memory() {
    mem.resize(1024, 0);

    // 🔥 DO NOT initialize caches here (they come from CPU/main)
    L1D = nullptr;
    L1I = nullptr;
    L2  = nullptr;

    memory_latency = 20;

    total_accesses = 0;
    total_misses = 0;
}

// 🔥 LOAD
int Memory::load(int address, int &latency) {

    bool hitL1 = false, hitL2 = false;

    latency = 0;
    total_accesses++;

    // L1D access
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

// 🔥 STORE
int Memory::store(int address, int value, int &latency) {

    bool hitL1 = false, hitL2 = false;

    latency = 0;
    total_accesses++;

    // L1D access
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

// 🔥 INSTRUCTION FETCH
int Memory::fetch_instruction(int address, int &latency) {

    bool hitL1 = false, hitL2 = false;

    latency = 0;
    total_accesses++;

    // L1I access
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