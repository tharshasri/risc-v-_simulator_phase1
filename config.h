#ifndef CONFIG_H
#define CONFIG_H

#include <unordered_map>
#include <string>

class Config {
<<<<<<< HEAD
public:
    std::unordered_map<std::string,int> latency;
=======

public:
    std::unordered_map<std::string, int> latency;
>>>>>>> 0007a5e61e9073c07bebc08e75a8e23e76a84be8

    void loadConfig(std::string filename);
    int getLatency(std::string opcode);
};

#endif