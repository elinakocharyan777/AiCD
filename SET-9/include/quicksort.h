#pragma once
#include <vector>
#include <string>
#include <utility>
#include "char_compare.h"

inline void quickSortImpl(std::vector<std::string>& a, int l, int r, CharCmpCounter& cc) {
    int i = l, j = r;
    const std::string pivot = a[l + (r - l) / 2];

    while (i <= j) {
        while (lessLexCharCount(a[i], pivot, cc)) i++;
        while (lessLexCharCount(pivot, a[j], cc)) j--;
        if (i <= j) {
            std::swap(a[i], a[j]);
            i++; j--;
        }
    }
    if (l < j) quickSortImpl(a, l, j, cc);
    if (i < r) quickSortImpl(a, i, r, cc);
}

inline void quickSort(std::vector<std::string>& a, CharCmpCounter& cc) {
    if (!a.empty()) quickSortImpl(a, 0, static_cast<int>(a.size()) - 1, cc);
}
