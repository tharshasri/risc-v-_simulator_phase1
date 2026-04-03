#include "config.h"
#include <fstream>
<<<<<<< HEAD
=======
#include <sstream>
>>>>>>> 0007a5e61e9073c07bebc08e75a8e23e76a84be8
#include <iostream>

void Config::loadConfig(std::string filename) {

    std::ifstream file(filename);

<<<<<<< HEAD
=======
    if(!file) {
        std::cout << "Error opening config file\n";
        return;
    }

>>>>>>> 0007a5e61e9073c07bebc08e75a8e23e76a84be8
    std::string op;
    int lat;

    while(file >> op >> lat) {
        latency[op] = lat;
    }
}

int Config::getLatency(std::string opcode) {

    if(latency.find(opcode) != latency.end())
        return latency[opcode];

<<<<<<< HEAD
    return 1;
=======
    return 1; // default latency
>>>>>>> 0007a5e61e9073c07bebc08e75a8e23e76a84be8
}