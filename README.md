# CS485G-Project1
Implementation of multi-hashing, cuckoo, and d-left hash tables in c++

# Reflection
- If I had known before hand that I was supposed to come up with my own hashing algorithm and used it as a master hash with seeds, I would not have utilized the weird combination hashes that I did.
- I converted the hash functions given to us as examples by the professor and converted them to a c++ formatting and wish I had just done the simpler thing
- A lot of type conversions happened that were completely unnecessary and are probably the reason of why my algorithms don't work as efficiently as I believe they should.

# How to Run
1. Use your compiler of choice, for examples I used the download of MinGW and the g++/gcc compiler
2. Run the line, "g++ HashAlgorithm.cpp hashes.cpp -o thishash.exe"
    - HashAlgorithm.cpp will just be replaced with the name of the cpp file you wish to compile, e.g. multiHash.cpp or cuckoo.cpp
3. Execute the compiled program and watch the results print out into the terminal 

# hashes.cpp
- A file that goes along with its corresponding header file for functions I commonly use throughout all 3 algorithms
- Not much to comment on, most of all the function definitions are commented and explain what they do, or are just self explanatory, like printTable

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
- The d-left hash implementation file
- Compared to cuckoo hash, d-left hash was supposed to be better and implemented correctly, it should have been more efficient and successfully inserted more flows. I only saw about 87% of the flows being inserted when in comparison I should have seen 90%-95% of the flows being inserted
- This was about the same number of flows that were inserted using cuckoo hash which is wrong. I believe the shortcoming to come from the lack of independence between hashing algorithms that I've used, since both the 3rd and 4th hashing algorithms for my 3rd and 4th partitions in the hash table were generated using a combination of two hashing algorithms.
- I believe with more independent hashing algorithms it would go better, but just like any other d-left hashing implementation, it still attempts to do each partition first 