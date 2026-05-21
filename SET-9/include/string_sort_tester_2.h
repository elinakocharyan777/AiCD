#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <stdexcept>
#include <algorithm>
#include "char_compare.h"
#include "quicksort.h"
#include "mergesort.h"

struct SortResult {
    double avg_time_us = 0.0;
    double avg_char_cmps = 0.0;
};

class StringSortTester {
public:
    explicit StringSortTester(int repeats = 7) : repeats_(repeats) {}

    SortResult runQuickSort(const std::vector<std::string>& data) const {
        return run(data, [](std::vector<std::string>& a, CharCmpCounter& cc) { quickSort(a, cc); });
    }

    SortResult runMergeSort(const std::vector<std::string>& data) const {
        return run(data, [](std::vector<std::string>& a, CharCmpCounter& cc) { mergeSort(a, cc); });
    }

private:
    int repeats_;

    template <class SortFunc>
    SortResult run(const std::vector<std::string>& data, SortFunc sorter) const {
        long long total_us = 0;
        long long total_char = 0;

        for (int t = 0; t < repeats_; ++t) {
            std::vector<std::string> a = data; // copy input
            CharCmpCounter cc;
            cc.reset();

            auto st = std::chrono::steady_clock::now();
            sorter(a, cc);
            auto en = std::chrono::steady_clock::now();

            if (!std::is_sorted(a.begin(), a.end())) {
                throw std::runtime_error("Sort produced incorrect order!");
            }

            long long us = std::chrono::duration_cast<std::chrono::microseconds>(en - st).count();
            total_us += us;
            total_char += cc.cnt;
        }

        SortResult res;
        res.avg_time_us = static_cast<double>(total_us) / repeats_;
        res.avg_char_cmps = static_cast<double>(total_char) / repeats_;
        return res;
    }
};
