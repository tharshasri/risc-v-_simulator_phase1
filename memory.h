#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

class Memory {
public:
    std::vector<int> mem;

    Memory();
    int load(int address);
    void store(int address, int value);
};

#endif