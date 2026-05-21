#pragma once
#include <string>
#include <algorithm>

struct CharCmpCounter {
    long long cnt = 0;
    void reset() { cnt = 0; }
};
inline bool lessLexCharCount(const std::string& a, const std::string& b, CharCmpCounter& cc) {
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b.size());
    const int L = std::min(n, m);
    for (int i = 0; i < L; ++i) {
        cc.cnt++; 
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return n < m;
}
