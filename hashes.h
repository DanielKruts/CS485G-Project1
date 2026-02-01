#ifndef hashes_h
#define hashes_h
#include <cstdint>
#include <string>

// FNV hash for string
int32_t FNVHash1(const std::string& data);

// FNV hash for two 64-bit keys
int32_t FNVHash1(int64_t key1, int64_t key2);

// FNV hash for single 64-bit key
int32_t FNVHash1(int64_t key);

// Thomas Wang integer hash
int32_t intHash(int32_t key);

#endif