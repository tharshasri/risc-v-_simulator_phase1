#include "cache.h"
#include <iostream>
using namespace std;

Cache::Cache(int s, int b, int a, int lat) {
    size = s;
    block_size = b;
    associativity = a;
    latency = lat;

    num_sets = (size / block_size) / associativity;
    sets.resize(num_sets, vector<CacheLine>(associativity));

    access_counter = 0;
}

int Cache::access(int address, bool &hit) {
    access_counter++;

    int block_addr = address / block_size;
    int index = block_addr % num_sets;
    int tag = block_addr / num_sets;

    // Check HIT
    for (int i = 0; i < associativity; i++) {
        if (sets[index][i].valid && sets[index][i].tag == tag) {
            hit = true;
            sets[index][i].last_used = access_counter;
            return latency;
        }
    }

    // MISS → LRU replacement
    hit = false;

    int lru_index = 0;
    int min_used = sets[index][0].last_used;

    for (int i = 1; i < associativity; i++) {
        if (!sets[index][i].valid) {
            lru_index = i;
            break;
        }
        if (sets[index][i].last_used < min_used) {
            min_used = sets[index][i].last_used;
            lru_index = i;
        }
    }

    sets[index][lru_index].valid = true;
    sets[index][lru_index].tag = tag;
    sets[index][lru_index].last_used = access_counter;

    return latency;
}