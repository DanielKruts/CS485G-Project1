#include <iostream>
#include <vector>
#include "hashes.h"

// Global Variables
const int TABLE_SIZE = 1000;
const int NUM_FLOWS = 1000;
const int NUM_HASHES = 4;//Number of partitions or sections for the d-left hashing, each segment is 250 indexes
const int PARTITION_SIZE = TABLE_SIZE / NUM_HASHES;//The size of each partition in the hash table

using namespace std;

bool insertFlow(int flowID, vector<int>& hashTable){
    uint32_t index;
    int local;
    for (int i = 0; i < NUM_HASHES; i++){
        //Which hash is used at which value i, or on paper, would be d(Number of partitions in the hash table)
        switch(i){
            case 0:
                local = static_cast<uint32_t>(FNVHash1(flowID)) % PARTITION_SIZE;
                break;
            case 1:
                local = static_cast<uint32_t>(intHash(flowID)) % PARTITION_SIZE;
                break;
            case 2://Combined hash of 1 and 2, shifting to the left and XORing to make it asymmetric
                local = (static_cast<uint32_t>(FNVHash1(flowID)) ^ (static_cast<uint32_t>(intHash(flowID)) << 1)) % PARTITION_SIZE;
                break;
            case 3://Another combined hash that does about the same but flops what hash gets shifted
                local = (static_cast<uint32_t>(intHash(flowID)) ^ (static_cast<uint32_t>(FNVHash1(flowID) << 2))) % PARTITION_SIZE;
                break;
        }

        index = i * PARTITION_SIZE + local;

        if(hashTable[index] == 0){
            hashTable[index] = flowID;
            return true;
        }
    }
    cout << "flowID: " << flowID << " dropped, failure to insert." << endl;
    return false;
}
int main(){
    vector<int> hashTable(TABLE_SIZE, 0);
    vector<int> flows;
    createFlowIDs(flows, NUM_FLOWS);
    int flowCount = 0;//Number of flows successfully inserted into the table

    for(int i = 0; i < NUM_FLOWS; i++){
        if(insertFlow(flows[i], hashTable)){
            flowCount++;
        }
    }
    printTable(hashTable, flowCount);
    return 0;
}