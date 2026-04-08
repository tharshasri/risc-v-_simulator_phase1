#include "config.h"
#include <fstream>
#include <iostream>

void Config::loadConfig(std::string filename) {

    std::ifstream file(filename);

    // 🔴 Check if file opened
    if (!file) {
        std::cout << "Error opening config file\n";
        return;
    }

    std::string op;
    int lat;

    // 🔴 Read instruction latency
    while (file >> op >> lat) {
        latency[op] = lat;
    }

    file.close();
}

int Config::getLatency(std::string opcode) {

    if (latency.find(opcode) != latency.end()) {
        return latency[opcode];
    }

    return 1; // default latency
}