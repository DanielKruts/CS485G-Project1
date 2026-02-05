#include <iostream>
#include <vector>
#include <fstream>
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
        // Apply multiple hash functions to obtain the possible index positions of the current flowID
        int index1, index2, index3;
        hashCompute(flowID, index1, index2, index3);
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
    printTable(hashTable, flowCount);

    //Create output
    ofstream outputFile;
    outputFile.open("multiHash.txt");
    outputFile << "Total Flows Inserted: " << flowCount << " out of " << NUM_FLOWS << endl;
    for (int i = 0; i < TABLE_SIZE; i++){
        outputFile << "Index: " << i << " Flow ID: " << hashTable[i] << endl;
    }
    outputFile.close();
    return 0;   
}