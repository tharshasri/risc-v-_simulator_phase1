#ifndef CONFIG_H
#define CONFIG_H

#include <unordered_map>
#include <string>

class Config {

public:

   

    std::unordered_map<std::string, int> latency;

   

    int virtualSize = 65536;

    int physicalSize = 16384;

    int pageSize = 4096;

    int dtlbEntries = 4;

    int tlbHitLatency = 1;

    int pageWalkLatency = 10;

    int pageFaultLatency = 50;

    std::string replacementPolicy = "fifo";

    
    void loadConfig(std::string filename);

    int getLatency(std::string opcode);
};

#endif