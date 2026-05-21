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

    if (!a.empty()) sort3way(a, 0, (int)a.size() - 1, 0);

    for (const auto& s : a) {
        cout << s << "\n";
    }
    return 0;
}