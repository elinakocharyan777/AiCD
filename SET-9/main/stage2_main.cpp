#include <bits/stdc++.h>
using namespace std;

#include "string_sort_tester.h"

// Put your Stage-1 StringGenerator in a header named string_generator.h
// or change this include to match your file name.
#include "string_generator.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    StringGenerator gen;
    auto base = gen.generateRandomBase(3000);

    StringSortTester tester(7);

    cout << "algo,dataset,n,avg_time_us,avg_char_cmps\n";

    for (int n = 100; n <= 3000; n += 100) {
        auto arr = gen.takeFirstN(base, n);

        auto randomArr = arr;
        auto reversedArr = gen.makeReversedSorted(arr);
        auto nearlyArr = gen.makeNearlySorted(arr, StringGenerator::defaultSwaps(n));

        auto q1 = tester.runQuickSort(randomArr);
        cout << "QuickSort,random," << n << "," << q1.avg_time_us << "," << q1.avg_char_cmps << "\n";

        auto q2 = tester.runQuickSort(reversedArr);
        cout << "QuickSort,reversed," << n << "," << q2.avg_time_us << "," << q2.avg_char_cmps << "\n";

        auto q3 = tester.runQuickSort(nearlyArr);
        cout << "QuickSort,nearly," << n << "," << q3.avg_time_us << "," << q3.avg_char_cmps << "\n";

        auto m1 = tester.runMergeSort(randomArr);
        cout << "MergeSort,random," << n << "," << m1.avg_time_us << "," << m1.avg_char_cmps << "\n";

        auto m2 = tester.runMergeSort(reversedArr);
        cout << "MergeSort,reversed," << n << "," << m2.avg_time_us << "," << m2.avg_char_cmps << "\n";

        auto m3 = tester.runMergeSort(nearlyArr);
        cout << "MergeSort,nearly," << n << "," << m3.avg_time_us << "," << m3.avg_char_cmps << "\n";
    }

    return 0;
}
