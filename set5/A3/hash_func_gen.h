#pragma once
#include <bits/stdc++.h>

class HashFuncGen {
public:
    explicit HashFuncGen(uint64_t seed = 0x9e3779b97f4a7c15ULL) : seed_(seed) {}

    //возвращает 32-битное значение 
    uint32_t hash32(const std::string& s) const {
        uint64_t x = fnv1a64(s) ^ seed_;
        x = splitmix64(x);
        return (uint32_t)(x & 0xFFFFFFFFu);
    }

private:
    uint64_t seed_;

    static uint64_t fnv1a64(const std::string& s) {
        const uint64_t FNV_OFFSET = 1469598103934665603ULL;
        const uint64_t FNV_PRIME  = 1099511628211ULL;
        uint64_t h = FNV_OFFSET;
        for (unsigned char c : s) {
            h ^= (uint64_t)c;
            h *= FNV_PRIME;
        }
        return h;
    }

    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
};