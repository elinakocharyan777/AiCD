#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <stdexcept>
#include <algorithm>
#include "char_ops.h"
#include "string_quicksort_3way_inst.h"
#include "msd_radix_inst.h"
#include "string_mergesort_lcp_inst.h"

struct SortResult3 {
    double avg_time_us = 0.0;
    double avg_char_ops = 0.0;
};

class StringSortTesterStage3 {
public:
    explicit StringSortTesterStage3(int repeats = 7) : repeats_(repeats) {}

    SortResult3 runStringQuickSort3Way(const std::vector<std::string>& data) const {
        return run(data, [](std::vector<std::string>& a, CharOpsCounter& ops){ stringQuickSort3Way(a, ops); });
    }

    SortResult3 runStringMergeSortLCP(const std::vector<std::string>& data) const {
        return run(data, [](std::vector<std::string>& a, CharOpsCounter& ops){ stringMergeSortLCP(a, ops); });
    }

    SortResult3 runMSDRadix(const std::vector<std::string>& data) const {
        return run(data, [](std::vector<std::string>& a, CharOpsCounter& ops){ msdRadixSort(a, ops); });
    }

    SortResult3 runMSDRadixCutover(const std::vector<std::string>& data, int threshold = 74) const {
        return run(data, [threshold](std::vector<std::string>& a, CharOpsCounter& ops){ msdRadixSortCutover(a, ops, threshold); });
    }

private:
    int repeats_;

    template <class SortFunc>
    SortResult3 run(const std::vector<std::string>& data, SortFunc sorter) const {
        long long total_us = 0;
        long long total_ops = 0;

        for (int t = 0; t < repeats_; ++t) {
            std::vector<std::string> a = data;
            CharOpsCounter ops; ops.reset();

            auto st = std::chrono::steady_clock::now();
            sorter(a, ops);
            auto en = std::chrono::steady_clock::now();

            if (!std::is_sorted(a.begin(), a.end())) {
                throw std::runtime_error("Stage3 sort produced incorrect order!");
            }

            total_us += std::chrono::duration_cast<std::chrono::microseconds>(en - st).count();
            total_ops += ops.cnt;
        }

        SortResult3 r;
        r.avg_time_us = (double)total_us / repeats_;
        r.avg_char_ops = (double)total_ops / repeats_;
        return r;
    }
};
