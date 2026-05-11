#include "vm.h"
#include <iostream>

VirtualMemory::VirtualMemory(
    int vSize,
    int pSize,
    int pSizeBytes,
    int tlbSize,
    int tlbLat,
    int walkLat,
    int faultLat,
    std::string policy
) {

    virtualSize = vSize;
    physicalSize = pSize;
    pageSize = pSizeBytes;

    tlbEntries = tlbSize;

    tlbHitLatency = tlbLat;
    pageWalkLatency = walkLat;
    pageFaultLatency = faultLat;

    replacementPolicy = policy;

    numFrames = physicalSize / pageSize;

    frameUsed.resize(numFrames, false);

    tlb.resize(tlbEntries);

    for (int i = 0; i < tlbEntries; i++) {
        tlb[i].valid = false;
    }
}

int VirtualMemory::translateAddress(unsigned int virtualAddress, bool isWrite) {

    int vpn = virtualAddress / pageSize;
    int offset = virtualAddress % pageSize;

    // TLB CHECK
    for (auto &entry : tlb) {

        if (entry.valid && entry.vpn == vpn) {

            tlbHits++;

            translationCycles += tlbHitLatency;

            int physicalAddress =
                entry.pfn * pageSize + offset;

            return physicalAddress;
        }
    }

    // TLB MISS
    tlbMisses++;
    pageWalks++;

    translationCycles += pageWalkLatency;

    // PAGE TABLE CHECK
    if (pageTable.find(vpn) == pageTable.end()
        || !pageTable[vpn].valid) {

        // PAGE FAULT
        pageFaults++;

        translationCycles += pageFaultLatency;

        int allocatedFrame = -1;

        // FIND FREE FRAME
        for (int i = 0; i < numFrames; i++) {

            if (!frameUsed[i]) {
                allocatedFrame = i;
                frameUsed[i] = true;
                break;
            }
        }

        // PAGE REPLACEMENT
        if (allocatedFrame == -1) {

            evictions++;

            allocatedFrame = fifoQueue.front();
            fifoQueue.pop();

            for (auto &p : pageTable) {

                if (p.second.frame == allocatedFrame) {

                    if (p.second.dirty) {
                        dirtyEvictions++;
                    }

                    p.second.valid = false;
                    break;
                }
            }
        }

        pageTable[vpn] = {
            allocatedFrame,
            true,
            isWrite
        };

        fifoQueue.push(allocatedFrame);
    }

    // UPDATE DIRTY BIT
    if (isWrite) {
        pageTable[vpn].dirty = true;
    }

    // UPDATE TLB
    int replaceIndex = vpn % tlbEntries;

    tlb[replaceIndex] = {
        vpn,
        pageTable[vpn].frame,
        true
    };

    int physicalAddress =
        pageTable[vpn].frame * pageSize + offset;

    return physicalAddress;
}