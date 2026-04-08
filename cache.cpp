#include "cache.h"
#include <iostream>
#include <climits> 
using namespace std;

Cache::Cache(int s, int b, int a, int lat) {
    size = s;
    block_size = b;
    associativity = a;
    latency = lat;

    if (block_size == 0 || associativity == 0) {
        cout << "ERROR: block_size or associativity is 0\n";
        exit(1);
    }

    num_sets = (size / block_size) / associativity;

    if (num_sets == 0) {
        cout << "ERROR: num_sets is 0 → invalid cache config\n";
        exit(1);
    }

    sets.resize(num_sets, vector<CacheLine>(associativity));

    access_counter = 0;

    // 🔥 NEW
    total_accesses = 0;
    total_misses = 0;
}

int Cache::access(int address, bool &hit) {

    access_counter++;
    total_accesses++;   // 🔥 track accesses

    int block_addr = address / block_size;
    int index = block_addr % num_sets;
    int tag = block_addr / num_sets;

    // 🔥 CHECK HIT
    for (int i = 0; i < associativity; i++) {
        if (sets[index][i].valid && sets[index][i].tag == tag) {
            hit = true;

            cout << "CACHE HIT (Address: " << address << ")\n";

            sets[index][i].last_used = access_counter;
            return latency;
        }
    }

    // 🔥 MISS
    hit = false;
    total_misses++;   // 🔥 track misses

    cout << "CACHE MISS (Address: " << address << ")\n";

    int lru_index = -1;
    int min_used = INT_MAX;

    // 🔥 find empty OR LRU
    for (int i = 0; i < associativity; i++) {
        if (!sets[index][i].valid) {
            lru_index = i;
            break;
        }

        if (sets[index][i].last_used < min_used) {
            min_used = sets[index][i].last_used;
            lru_index = i;
        }
    }

    // 🔥 replace line
    sets[index][lru_index].valid = true;
    sets[index][lru_index].tag = tag;
    sets[index][lru_index].last_used = access_counter;

    return latency;
}