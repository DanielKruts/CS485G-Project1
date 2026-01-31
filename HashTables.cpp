#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// Global Variables
const int TABLE_SIZE = 1000;
const int NUM_FLOWS = 1000;
const int NUM_HASHES = 3;

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

int main(){
    // Multi-Hashing Table
    vector<int> hashTable(TABLE_SIZE, 0);
    //Create all the flowID's for hashing
    vector<int> flows;
    for (int i = 1; i <= NUM_FLOWS; i++){
            flows.push_back(i);
    }
    // Shuffles the flow IDs for randomization
    // The shuffle function used was an example I found online that is an implementation of the Fisher-Yates shuffle
    // This uses a random number generated to be the seed and different seeds create different shuffles
    // If the seed happens to somehow be the same number, the shuffle will always be the same, but I used this for a simple pseudo-random function
    random_device rd;
    mt19937 g(rd());
    //Important note, although the random seeds are supposed to be different, on Windows MinGW system, 
    //the randomness seems to be deterministic
    shuffle(flows.begin(), flows.end(), g);


    for(int i = 0; i < NUM_FLOWS; i++){
        int flowID = flows[i];
        // Apply multiple hash functions
        uint32_t hash1 = static_cast<uint32_t>(FNVHash1(flowID));
        uint32_t hash2 = static_cast<uint32_t>(intHash(flowID));
        uint32_t hash3 = hash1 ^ (hash2 << 1);

        cout << "Flow ID: " << flowID << " Hashes: " << hash1 << ", " << hash2 << ", " << hash3 << endl;

        //Creates the possible index numbers where the flowID can be inserted
        int index1 = hash1 % TABLE_SIZE;
        int index2 = hash2 % TABLE_SIZE;
        int index3 = hash3 % TABLE_SIZE;
        //Attempts to insert into the hash table if a flowID is not already present
        if (hashTable[index1] == 0){
            hashTable[index1] = flowID;
        }else if (hashTable[index2] == 0){
            hashTable[index2] = flowID;
        }else if (hashTable[index3] == 0){
            hashTable[index3] = flowID;
        }else {//Collision occured, no available slots
            cout << "Collision occurred for Flow ID: " << flowID << endl;
            continue;
        }
    }
    

    for (int i = 0; i < TABLE_SIZE; i++){
        if (hashTable[i] != 0){
            cout << "Index: " << i << " Flow ID: " << hashTable[i] << endl;
        }
    }

    return 0;   
}