#include "config.h"
#include <fstream>
#include <iostream>

void Config::loadConfig(std::string filename) {

    std::ifstream file(filename);

    std::string op;
    int lat;

    while(file >> op >> lat) {
        latency[op] = lat;
    }
}

int Config::getLatency(std::string opcode) {

    if(latency.find(opcode) != latency.end())
        return latency[opcode];

    return 1;
}