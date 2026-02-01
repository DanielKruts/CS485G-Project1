#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "hashes.h"

using namespace std;

// Global Variables
const int TABLE_SIZE = 1000;
const int NUM_FLOWS = 1000;
const int NUM_HASHES = 3;

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