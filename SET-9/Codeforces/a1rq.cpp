#include <bits/stdc++.h>
using namespace std;
static inline int charAt(const string& s, int d) {
    if (d < 0 || d >= (int)s.size()) return -1;
    return (unsigned char)s[d];
}

static void sort3way(vector<string>& a, int lo, int hi, int d) {
    if (hi <= lo) return;

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v) {
            swap(a[lt], a[i]);
            lt++; i++;
        } else if (t > v) {
            swap(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }

    sort3way(a, lo, lt - 1, d);
    if (v >= 0) sort3way(a, lt, gt, d + 1);
    sort3way(a, gt + 1, hi, d);
}

static void msdSort(vector<string>& a, int lo, int hi, int d, vector<string>& aux) {
    if (hi <= lo) return;
    if (hi - lo + 1 < 74) {
        sort3way(a, lo, hi, d);
        return;
    }

    const int R = 256;     
    const int B = R + 1;   

    int freq[B];
    memset(freq, 0, sizeof(freq));

    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d);
        freq[c + 1]++;
    }

    int start[B + 1];
    start[0] = 0;
    for (int b = 0; b < B; ++b) start[b + 1] = start[b] + freq[b];

    int next[B + 1];
    for (int b = 0; b <= B; ++b) next[b] = start[b];

    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d);
        int b = c + 1;
        aux[next[b]++] = std::move(a[i]);
    }

    for (int i = lo; i <= hi; ++i) {
        a[i] = std::move(aux[i - lo]);
    }

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
    getline(cin, dummy); 

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

    for (auto& s : a) cout << s << "\n";
    return 0;
}