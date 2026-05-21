#include <bits/stdc++.h>
using namespace std;

#include "string_sort_tester_stage3.h"
#include "string_generator.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    StringGenerator gen;
    auto base = gen.generateRandomBase(3000);

    StringSortTesterStage3 tester(7);

    cout << "algo,dataset,n,avg_time_us,avg_char_ops\n";

    for (int n = 100; n <= 3000; n += 100) {
        auto arr = gen.takeFirstN(base, n);

        auto randomArr = arr;
        auto reversedArr = gen.makeReversedSorted(arr);
        auto nearlyArr = gen.makeNearlySorted(arr, StringGenerator::defaultSwaps(n));

        // 1) 3-way String QuickSort
        auto q = tester.runStringQuickSort3Way(randomArr);
        cout << "StringQuickSort,random," << n << "," << q.avg_time_us << "," << q.avg_char_ops << "\n";
        q = tester.runStringQuickSort3Way(reversedArr);
        cout << "StringQuickSort,reversed," << n << "," << q.avg_time_us << "," << q.avg_char_ops << "\n";
        q = tester.runStringQuickSort3Way(nearlyArr);
        cout << "StringQuickSort,nearly," << n << "," << q.avg_time_us << "," << q.avg_char_ops << "\n";

        // 2) String MergeSort (LCP)
        auto m = tester.runStringMergeSortLCP(randomArr);
        cout << "StringMergeSortLCP,random," << n << "," << m.avg_time_us << "," << m.avg_char_ops << "\n";
        m = tester.runStringMergeSortLCP(reversedArr);
        cout << "StringMergeSortLCP,reversed," << n << "," << m.avg_time_us << "," << m.avg_char_ops << "\n";
        m = tester.runStringMergeSortLCP(nearlyArr);
        cout << "StringMergeSortLCP,nearly," << n << "," << m.avg_time_us << "," << m.avg_char_ops << "\n";

        // 3) MSD radix (no cutover)
        auto r = tester.runMSDRadix(randomArr);
        cout << "MSDRadix,random," << n << "," << r.avg_time_us << "," << r.avg_char_ops << "\n";
        r = tester.runMSDRadix(reversedArr);
        cout << "MSDRadix,reversed," << n << "," << r.avg_time_us << "," << r.avg_char_ops << "\n";
        r = tester.runMSDRadix(nearlyArr);
        cout << "MSDRadix,nearly," << n << "," << r.avg_time_us << "," << r.avg_char_ops << "\n";

        // 4) MSD radix + cutover
        auto rc = tester.runMSDRadixCutover(randomArr, 74);
        cout << "MSDRadixCutover,random," << n << "," << rc.avg_time_us << "," << rc.avg_char_ops << "\n";
        rc = tester.runMSDRadixCutover(reversedArr, 74);
        cout << "MSDRadixCutover,reversed," << n << "," << rc.avg_time_us << "," << rc.avg_char_ops << "\n";
        rc = tester.runMSDRadixCutover(nearlyArr, 74);
        cout << "MSDRadixCutover,nearly," << n << "," << rc.avg_time_us << "," << rc.avg_char_ops << "\n";
    }

    return 0;
}
