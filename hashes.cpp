#include "hashes.h"
#include <string>
#include <random>
#include <vector>
#include <algorithm>

const int TABLE_SIZE = 1000;

using namespace std;
// Section of hash functions that were given and converted into a format friendly for c++
/* FNV Hash for string */
int32_t FNVHash1(const string& data) {
    const int32_t p = 16777619;
    int32_t hash = static_cast<int32_t>(2166136261UL);

    for (unsigned char c : data) {
        hash = (hash ^ c) * p;
    }

    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;

    return hash;
}
/* FNV Hash for long key */
int32_t FNVHash1(int64_t key) {
    key = (~key) + (key << 18);
    key ^= (key >> 31);
    key *= 21;
    key ^= (key >> 11);
    key += (key << 6);
    key ^= (key >> 22);

    return static_cast<int32_t>(key);
}
/* FNV Hash for two long keys */
int32_t FNVHash1(int64_t key1, int64_t key2) {
    return FNVHash1((key1 << 32) | key2);
}
/* Thomas Wang integer hash */
int32_t intHash(int32_t key) {
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}
void createFlowIDs(vector<int>& flows, int numFlows){
    for (int i = 1; i <= numFlows; i++){
            flows.push_back(i);
    }
    /* Shuffles the flow IDs for randomization
     The shuffle function used was an example I found online that is an implementation of the Fisher-Yates shuffle
     This uses a random number generated to be the seed and different seeds create different shuffles
     This creates randomness in what flow IDs are inserted first into the hash table, allowing for the simulation to
     show that not every flow ID can be inserted due to collisions even if the hashes and the number of flows stay the same in each
     iteration of the program.
    */
    random_device rd;
    mt19937 g(rd());
    shuffle(flows.begin(), flows.end(), g);
}
//The function to compute all three hashes for a given flowID
void hashCompute(int flowID, int& index1, int& index2, int& index3){
    // Apply the two hash functions and then the third combined hash
    uint32_t hash1 = static_cast<uint32_t>(FNVHash1(flowID));
    uint32_t hash2 = static_cast<uint32_t>(intHash(flowID));
    uint32_t hash3 = hash1 ^ (hash2 << 1);

    //Creates the possible index numbers where the flowID can be inserted
    index1 = hash1 % TABLE_SIZE;
    index2 = hash2 % TABLE_SIZE;
    index3 = hash3 % TABLE_SIZE;
}