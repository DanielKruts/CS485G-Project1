#include <iostream>
#include <vector>
#include "hashes.h"

using namespace std;

// Global Variables
const int TABLE_SIZE = 1000;
const int NUM_FLOWS = 1000;
const int NUM_HASHES = 3;
const int NUM_STEPS = 2;

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

bool cuckooInsert(vector<int>& hashTable, int flowID){
    int cur = flowID;
    vector<int> tempTable = hashTable;
    
    //Cuckoo Insertion Logic
    for (int j = 0; j < NUM_STEPS; j++){
        int index1, index2, index3;
        hashCompute(cur, index1, index2, index3);
        
        //Check for any empty slots
        if(tempTable[index1] == 0){
            tempTable[index1] = cur;
            hashTable = tempTable;
            return true;
        }else if(tempTable[index2] == 0){
            tempTable[index2] = cur;
            hashTable = tempTable;
            return true;
        }else if(tempTable[index3] == 0){
            tempTable[index3] = cur;
            hashTable = tempTable;
            return true;
        }

        //No more empty slots and we have exceeded the number of steps allowed, drop value, insertion failed
        if(j == NUM_STEPS - 1){
            cout << "Insertion failed for Flow ID: " << cur << endl;
            return false;
        }

        int evictIndex;
        //Evictions Logic
        if(j % 3 == 0){
            evictIndex = index1;
        }else if(j % 3 == 1){
            evictIndex = index2;
        }else{
            evictIndex = index3;
        }
        
        swap(flowID, tempTable[evictIndex]);
    }
    return false;
}

//Cuckoo Hash Optimization Implementation
int main(){
    vector<int> hashTable(TABLE_SIZE, 0);
    int flowCount = 0;//Number of flows successfully inserted
    //Create all the flowID's for hashing
    vector<int> flows;
    createFlowIDs(flows, NUM_FLOWS);

    for(int i = 0; i < NUM_FLOWS; i++){
        bool result = cuckooInsert(hashTable, flows[i]);//The result of whether the insertion was successful or not
        if(!result){
            cout << "Failed to insert Flow ID: " << flows[i] << endl;
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