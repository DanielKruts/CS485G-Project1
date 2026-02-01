#include <iostream>
#include <vector>
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
    int flowCount = 0;
    createFlowIDs(flows, NUM_FLOWS);
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
        flowCount++;
    }
    
    cout << "Total Flows Inserted: " << flowCount << " out of " << NUM_FLOWS << endl;
    for (int i = 0; i < TABLE_SIZE; i++){
            cout << "Index: " << i << " Flow ID: " << hashTable[i] << endl;
    }

    return 0;   
}