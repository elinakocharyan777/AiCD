#pragma once
#include <vector>
#include <string>
#include <utility>
#include "char_ops.h"

inline void stringQuickSort3WayImpl(std::vector<std::string>& a, int lo, int hi, int d, CharOpsCounter& ops) {
    if (hi <= lo) return;

    int lt = lo, gt = hi;
    int v = charAtCount(a[lo], d, ops);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAtCount(a[i], d, ops);
        if (t < v) {
            std::swap(a[lt], a[i]);
            lt++; i++;
        } else if (t > v) {
            std::swap(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }

    stringQuickSort3WayImpl(a, lo, lt - 1, d, ops);
    if (v >= 0) stringQuickSort3WayImpl(a, lt, gt, d + 1, ops);
    stringQuickSort3WayImpl(a, gt + 1, hi, d, ops);
}

inline void stringQuickSort3Way(std::vector<std::string>& a, CharOpsCounter& ops) {
    if (!a.empty()) stringQuickSort3WayImpl(a, 0, (int)a.size() - 1, 0, ops);
}
