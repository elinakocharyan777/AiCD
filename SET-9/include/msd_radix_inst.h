#pragma once
#include <vector>
#include <string>
#include <utility>
#include <cstring>
#include "char_ops.h"
#include "string_quicksort_3way_inst.h"

inline void msdSortImpl(std::vector<std::string>& a, int lo, int hi, int d,
                        std::vector<std::string>& aux,
                        CharOpsCounter& ops,
                        bool cutover,
                        int cutover_threshold) {
    if (hi <= lo) return;

    if (cutover && (hi - lo + 1 < cutover_threshold)) {
        stringQuickSort3WayImpl(a, lo, hi, d, ops);
        return;
    }

    const int R = 256;
    const int B = R + 1; 

    int freq[B];
    std::memset(freq, 0, sizeof(freq));

    for (int i = lo; i <= hi; ++i) {
        int c = charAtCount(a[i], d, ops);
        freq[c + 1]++;
    }

    int start[B + 1];
    start[0] = 0;
    for (int b = 0; b < B; ++b) start[b + 1] = start[b] + freq[b];

    int next[B + 1];
    for (int b = 0; b <= B; ++b) next[b] = start[b];

    for (int i = lo; i <= hi; ++i) {
        int c = charAtCount(a[i], d, ops);
        int b = c + 1;
        aux[next[b]++] = std::move(a[i]);
    }

    for (int i = lo; i <= hi; ++i) a[i] = std::move(aux[i - lo]);

    for (int b = 1; b < B; ++b) {
        int subLo = lo + start[b];
        int subHi = lo + start[b + 1] - 1;
        if (subHi > subLo) {
            msdSortImpl(a, subLo, subHi, d + 1, aux, ops, cutover, cutover_threshold);
        }
    }
}

inline void msdRadixSort(std::vector<std::string>& a, CharOpsCounter& ops) {
    if (a.empty()) return;
    std::vector<std::string> aux(a.size());
    msdSortImpl(a, 0, (int)a.size() - 1, 0, aux, ops, false, 0);
}

inline void msdRadixSortCutover(std::vector<std::string>& a, CharOpsCounter& ops, int threshold = 74) {
    if (a.empty()) return;
    std::vector<std::string> aux(a.size());
    msdSortImpl(a, 0, (int)a.size() - 1, 0, aux, ops, true, threshold);
}
