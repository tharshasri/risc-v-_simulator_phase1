#include "memory.h"

Memory::Memory() {
    mem.resize(1024, 0);  
}

int Memory::load(int address) {
    return mem[address];
}

void Memory::store(int address, int value) {
    mem[address] = value;
}