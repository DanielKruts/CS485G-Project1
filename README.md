# CS485G-Project1
Implementation of multi-hashing, cuckoo, and d-left hash tables in c++

# How to Run
1. Use your compiler of choice, for examples I used the download of MinGW and the g++/gcc compiler
2. Run the line, "g++ HashAlgorithm.cpp hashes.cpp -o thishash.exe"
    - HashAlgorithm.cpp will just be replaced with the name of the cpp file you wish to compile, e.g. multiHash.cpp or cuckoo.cpp
3. Execute the compiled program and watch the results print out into the terminal 

# multiHash.cpp
- The multi hash implementation file
- It takes a number of 1000 randomly generated flowIDs and hashes them all and tries to find space for them in the hash table.
- If all 3 hashes result in the possible indices being all taken up by another flowID, then the flowID is dropped
- Prints out onto the terminal how many flows were successfully inserted in comparsion to the number of flowIDs generated and then prints out the contents of the hash table

# cuckoo.cpp
- The cuckoo hash implementation file
- Like Multi hash, takes the randomly generated flowIDs and hashes them all and tries to find the space for them in the hash table.
- Slightly different, as now, we can do swaps to attempt to insert the flowID into a valid index of the hashmap
- It does this by first seeing if the 3 indexes are empty, if one of them is, insert it into the "closest" index, or the highest priority
- If there are no available indexes to insert into, the program tests for the possiblity of swapping flowIDs to a new index
- If all of this fails, then the insertion fails and we drop the flowID from being inserted into the table

# dLeft.cpp
