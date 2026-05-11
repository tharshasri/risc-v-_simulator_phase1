#include "config.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Config::loadConfig(std::string filename) {

    std::ifstream file(filename);


    if (!file) {

        std::cout
            << "Error opening config file\n";

        return;
    }

    std::string line;

  

    while (getline(file, line)) {


        if (line.empty()) {
            continue;
        }


        if (line[0] == '[') {
            continue;
        }


        if (line.find('=') != std::string::npos) {

            std::stringstream ss(line);

            std::string key;
            std::string value;

            getline(ss, key, '=');
            getline(ss, value);


            while (!key.empty() && key[0] == ' ')
                key.erase(0, 1);

            while (!key.empty() && key.back() == ' ')
                key.pop_back();

            while (!value.empty() && value[0] == ' ')
                value.erase(0, 1);

            while (!value.empty() && value.back() == ' ')
                value.pop_back();

            if (key == "virtual_size_bytes") {

                virtualSize =
                    std::stoi(value);
            }

            else if (key == "physical_size_bytes") {

                physicalSize =
                    std::stoi(value);
            }

            else if (key == "page_size_bytes") {

                pageSize =
                    std::stoi(value);
            }

            else if (key == "dtlb_entries") {

                dtlbEntries =
                    std::stoi(value);
            }

            else if (key == "tlb_hit_latency") {

                tlbHitLatency =
                    std::stoi(value);
            }

            else if (key == "page_walk_latency") {

                pageWalkLatency =
                    std::stoi(value);
            }

            else if (key == "page_fault_latency") {

                pageFaultLatency =
                    std::stoi(value);
            }

            else if (key == "replacement_policy") {

                replacementPolicy =
                    value;
            }


            else {

                try {

                    latency[key] =
                        std::stoi(value);
                }

                catch (...) {

                }
            }
        }


        else {

            std::stringstream ss(line);

            std::string op;

            int lat;

            if (ss >> op >> lat) {

                latency[op] = lat;
            }
        }
    }

    file.close();
}

int Config::getLatency(std::string opcode) {

    if (
        latency.find(opcode)
        !=
        latency.end()
    ) {

        return latency[opcode];
    }

  

    return 1;
}