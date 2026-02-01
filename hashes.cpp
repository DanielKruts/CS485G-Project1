#include "hashes.h"
#include <string>

using namespace std;
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