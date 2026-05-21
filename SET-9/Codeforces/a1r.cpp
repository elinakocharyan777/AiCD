#include <bits/stdc++.h>
using namespace std;

// MSD radix sort for strings (lexicographic order).
// Works for any byte characters. End-of-string is treated as -1 (smaller than any char).

static inline int charAt(const string& s, int d) {
    if (d < 0 || d >= (int)s.size()) return -1;
    return (unsigned char)s[d]; // 0..255
}

static void msdSort(vector<string>& a, int lo, int hi, int d, vector<string>& aux) {
    if (hi <= lo) return;

    const int R = 256;          // possible byte values
    const int B = R + 1;        // buckets: -1 plus 0..255 -> 257 buckets

    // freq[b] where b = c+1, c in [-1..255]
    int freq[B];
    memset(freq, 0, sizeof(freq));

    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d);
        freq[c + 1]++;
    }

    // start positions (prefix sums), size B+1
    int start[B + 1];
    start[0] = 0;
    for (int b = 0; b < B; ++b) {
        start[b + 1] = start[b] + freq[b];
    }

    // next positions for stable distribution
    int next[B + 1];
    for (int b = 0; b <= B; ++b) next[b] = start[b];

    // distribute to aux (stable)
    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d);
        int b = c + 1;
        aux[next[b]++] = std::move(a[i]);
    }

    // copy back
    for (int i = lo; i <= hi; ++i) {
        a[i] = std::move(aux[i - lo]);
    }

    // recurse for buckets with c >= 0 (skip bucket for c = -1)
    // bucket index b=0 corresponds to c=-1
    for (int b = 1; b < B; ++b) {
        int subLo = lo + start[b];
        int subHi = lo + start[b + 1] - 1;
        if (subHi > subLo) {
            msdSort(a, subLo, subHi, d + 1, aux);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy); // eat endline

    vector<string> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        a.push_back(std::move(s));
    }

    if (!a.empty()) {
        vector<string> aux(a.size());
        msdSort(a, 0, (int)a.size() - 1, 0, aux);
    }

    for (auto &s : a) {
        cout << s << "\n";
    }
    return 0;
}