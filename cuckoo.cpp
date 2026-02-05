#include <iostream>
#include <vector>
#include <fstream>
#include "hashes.h"

using namespace std;

// Global Variables
const int TABLE_SIZE = 1000;
const int NUM_FLOWS = 1000;
const int NUM_HASHES = 3;
const int NUM_STEPS = 2;

bool cuckooInsert(vector<int>& hashTable, int flowID){
    int cur = flowID;
    vector<int> tempTable = hashTable;
    int lastIndex = -1;
    //Cuckoo Insertion Logic
    for (int j = 0; j <= NUM_STEPS; j++){
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
        if(j == NUM_STEPS){
            return false;
        }

        int evictIndex;
        //Evictions Logic
        if(index1 != lastIndex){
            evictIndex = index1;
        }else if(index2 != lastIndex){
            evictIndex = index2;
        }else{
            evictIndex = index3;
        }
        
        swap(cur, tempTable[evictIndex]);
        lastIndex = evictIndex;
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
    printTable(hashTable, flowCount);
    
    //Create output
    ofstream outputFile;
    outputFile.open("cuckoo.txt");
    outputFile << "Total Flows Inserted: " << flowCount << " out of " << NUM_FLOWS << endl;
    for (int i = 0; i < TABLE_SIZE; i++){
        outputFile << "Index: " << i << " Flow ID: " << hashTable[i] << endl;
    }
    outputFile.close();
    return 0;
}