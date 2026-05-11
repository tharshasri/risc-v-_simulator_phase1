#ifndef VM_H
#define VM_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

struct TLBEntry {
    int vpn;
    int pfn;
    bool valid;
};

struct PageTableEntry {
    int frame;
    bool valid;
    bool dirty;
};

class VirtualMemory {
private:

    int virtualSize;
    int physicalSize;
    int pageSize;

    int numFrames;
    int tlbEntries;

    int tlbHitLatency;
    int pageWalkLatency;
    int pageFaultLatency;

    std::string replacementPolicy;

    std::vector<TLBEntry> tlb;

    std::unordered_map<int, PageTableEntry> pageTable;

    std::queue<int> fifoQueue;

    std::vector<bool> frameUsed;

public:

    int tlbHits = 0;
    int tlbMisses = 0;
    int pageWalks = 0;
    int pageFaults = 0;
    int evictions = 0;
    int dirtyEvictions = 0;
    int translationCycles = 0;

    VirtualMemory(
        int vSize,
        int pSize,
        int pSizeBytes,
        int tlbSize,
        int tlbLat,
        int walkLat,
        int faultLat,
        std::string policy
    );

    int translateAddress(unsigned int virtualAddress, bool isWrite);

};

#endif