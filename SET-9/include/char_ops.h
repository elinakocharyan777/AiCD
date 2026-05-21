#pragma once
#include <string>
#include <algorithm>

struct CharOpsCounter {
    long long cnt = 0;
    void reset() { cnt = 0; }
};
inline int charAtCount(const std::string& s, int d, CharOpsCounter& ops) {
    ops.cnt++;
    if (d < 0 || d >= (int)s.size()) return -1;
    return (unsigned char)s[d];
}
