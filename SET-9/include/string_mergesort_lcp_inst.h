#pragma once
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "char_ops.h"
inline int lcpCompareCount(const std::string& a, const std::string& b, int& lcp, CharOpsCounter& ops) {
    int i = 0;
    int n = (int)a.size();
    int m = (int)b.size();
    int L = std::min(n, m);

    while (i < L) {
        ops.cnt++; 
        if (a[i] != b[i]) break;
        i++;
    }
    lcp = i;

    if (i == L) {
        if (n == m) return 0;
        return (n < m) ? -1 : 1;
    }
    return (unsigned char)a[i] < (unsigned char)b[i] ? -1 : 1;
}

inline void mergeRangeLCP(std::vector<std::string>& a, std::vector<std::string>& tmp,
                          int l, int mid, int r, CharOpsCounter& ops) {
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        int lcp = 0;
        int cmp = lcpCompareCount(a[i], a[j], lcp, ops);
        if (cmp <= 0) tmp[k++] = std::move(a[i++]);
        else          tmp[k++] = std::move(a[j++]);
    }
    while (i < mid) tmp[k++] = std::move(a[i++]);
    while (j < r)   tmp[k++] = std::move(a[j++]);

    for (int t = l; t < r; ++t) a[t] = std::move(tmp[t]);
}

inline void mergeSortLCPImpl(std::vector<std::string>& a, std::vector<std::string>& tmp,
                             int l, int r, CharOpsCounter& ops) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;
    mergeSortLCPImpl(a, tmp, l, mid, ops);
    mergeSortLCPImpl(a, tmp, mid, r, ops);
    mergeRangeLCP(a, tmp, l, mid, r, ops);
}

inline void stringMergeSortLCP(std::vector<std::string>& a, CharOpsCounter& ops) {
    if (a.empty()) return;
    std::vector<std::string> tmp(a.size());
    mergeSortLCPImpl(a, tmp, 0, (int)a.size(), ops);
}
