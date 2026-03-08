#ifndef CONFIG_H
#define CONFIG_H

#include <unordered_map>
#include <string>

class Config {

public:
    std::unordered_map<std::string, int> latency;

    void loadConfig(std::string filename);
    int getLatency(std::string opcode);
};

#endif