#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "cache.h"

class Memory {
public:
    std::vector<int> mem;

    // 🔥 Cache pointers
    Cache *L1D;
    Cache *L1I;
    Cache *L2;

    int memory_latency;

    // Stats
    int total_accesses;
    int total_misses;

    Memory();

    int load(int address, int &latency);
    int store(int address, int value, int &latency);
    int fetch_instruction(int address, int &latency);
};

#endif