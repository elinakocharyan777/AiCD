#pragma once
#include <vector>
#include <string>
#include <utility>
#include "char_compare.h"

inline void mergeSortImpl(std::vector<std::string>& a,
                          std::vector<std::string>& tmp,
                          int l, int r,
                          CharCmpCounter& cc) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;

    mergeSortImpl(a, tmp, l, mid, cc);
    mergeSortImpl(a, tmp, mid, r, cc);

    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (lessLexCharCount(a[i], a[j], cc)) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];

    for (int t = l; t < r; ++t) a[t] = std::move(tmp[t]);
}

inline void mergeSort(std::vector<std::string>& a, CharCmpCounter& cc) {
    std::vector<std::string> tmp(a.size());
    mergeSortImpl(a, tmp, 0, static_cast<int>(a.size()), cc);
}
