#include <bits/stdc++.h>
using namespace std;
static inline int lcpCompare(const string& a, const string& b, int& lcp) {
    int i = 0;
    int n = (int)a.size();
    int m = (int)b.size();
    int L = min(n, m);

    while (i < L && a[i] == b[i]) i++;
    lcp = i;

    if (i == L) {
        if (n == m) return 0;
        return (n < m) ? -1 : 1; 
    }
    return (a[i] < b[i]) ? -1 : 1;
}

static void mergeRange(vector<string>& a, vector<string>& tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l;

    while (i < mid && j < r) {
        int lcp = 0;
        int cmp = lcpCompare(a[i], a[j], lcp); 
        if (cmp <= 0) tmp[k++] = std::move(a[i++]); 
        else          tmp[k++] = std::move(a[j++]);
    }
    while (i < mid) tmp[k++] = std::move(a[i++]);
    while (j < r)   tmp[k++] = std::move(a[j++]);

    for (int t = l; t < r; ++t) a[t] = std::move(tmp[t]);
}

static void mergeSortImpl(vector<string>& a, vector<string>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int mid = l + (r - l) / 2;
    mergeSortImpl(a, tmp, l, mid);
    mergeSortImpl(a, tmp, mid, r);
    mergeRange(a, tmp, l, mid, r);
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
        vector<string> tmp(a.size());
        mergeSortImpl(a, tmp, 0, (int)a.size());
    }

    for (auto& s : a) cout << s << "\n";
    return 0;
}