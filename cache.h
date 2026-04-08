#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cmath>
using namespace std;

struct CacheLine {
    bool valid;
    int tag;
    int last_used;

    CacheLine() {
        valid = false;
        tag = -1;
        last_used = 0;
    }
};

class Cache {
public:
    int size;
    int block_size;
    int associativity;
    int latency;

    int num_sets;
    int access_counter;

    // 🔥 NEW (for miss rate)
    int total_accesses;
    int total_misses;

    vector<vector<CacheLine>> sets;

    Cache() {}  // 🔥 needed for assignment later
    Cache(int s, int b, int a, int lat);

    int access(int address, bool &hit);
};

#endif