#ifndef hashes_h
#define hashes_h
#include <cstdint>
#include <string>
#include <vector>

using namespace std;
// FNV hash for string
int32_t FNVHash1(const string& data);

// FNV hash for two 64-bit keys
int32_t FNVHash1(int64_t key1, int64_t key2);

// FNV hash for single 64-bit key
int32_t FNVHash1(int64_t key);

// Thomas Wang integer hash
int32_t intHash(int32_t key);

// Create flow IDs
void createFlowIDs(vector<int>& flows, int numFlows);

//Compute 3 hashes for a given value and retuns their possible index locations in the hash table
void hashCompute(int value, int& index1, int& index2, int& index3);

//Function to print out the hashTable and the number of flows successfully inserted into the table
void printTable(vector<int> hashTable, int flowCount);

#endif