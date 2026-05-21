
#include <bits/stdc++.h>
using namespace std;

class StringGenerator {
    public:
        struct Config {
            int minLen = 10;
            int maxLen = 200;
            uint64_t seed = 42;
        };
        explicit StringGenerator() : cfg_(), rng_(cfg_.seed) {}
        explicit StringGenerator(const Config& cfg) : cfg_(cfg), rng_(cfg_.seed) {}
        static const string& alphabet() {
            static const string a =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789"
                "!@#%:;^&*()-."; 
            return a;
        }
        string randomString() {
            uniform_int_distribution<int> lenDist(cfg_.minLen, cfg_.maxLen);
            uniform_int_distribution<int> chDist(0, (int)alphabet().size() - 1);
            int len = lenDist(rng_);
            string s;
            s.reserve(len);
            for (int i = 0; i < len; ++i) {
                s.push_back(alphabet()[chDist(rng_)]);
            }
            return s;
        }
        vector<string> generateRandomBase(int nMax) {
            vector<string> a;
            a.reserve(nMax);
            for (int i = 0; i < nMax; ++i) a.push_back(randomString());
            return a;
        }
        vector<string> takeFirstN(const vector<string>& base, int n) const {
        assert(n >= 0 && n <= (int)base.size());
        return vector<string>(base.begin(), base.begin() + n);
    }
        //отсортированный массив  
        vector<string> makeSorted(vector<string> a) const {
            sort(a.begin(), a.end());
            return a;
        }
    
        //обратно отсортированный 
        vector<string> makeReversedSorted(vector<string> a) const {
            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
            return a;
        }
    
        // почти отсортированный
        vector<string> makeNearlySorted(vector<string> a, int swaps) {
            sort(a.begin(), a.end());
            uniform_int_distribution<int> posDist(0, (int)a.size() - 1);
    
            for (int t = 0; t < swaps; ++t) {
                int i = posDist(rng_);
                int j = posDist(rng_);
                if (i == j) continue;
                swap(a[i], a[j]);
            }
            return a;
        }
    
        //2% перестановок
        static int defaultSwaps(int n) {
            return max(1, (int)floor(0.02 * n));
        }
    
        // prefix-heavy массив
        vector<string> generatePrefixHeavyBase(int nMax, int prefixLen, int groups) {
            groups = max(1, groups);
            prefixLen = max(1, prefixLen);
    
            vector<string> pref(groups);
            for (int g = 0; g < groups; ++g) {
                pref[g] = randomFixedLen(prefixLen);
            }
            uniform_int_distribution<int> groupDist(0, groups - 1);
            vector<string> a;
            a.reserve(nMax);
            for (int i = 0; i < nMax; ++i) {
                int g = groupDist(rng_);
                string tail = randomString();
                string s = pref[g] + tail;
                if ((int)s.size() > cfg_.maxLen) s.resize(cfg_.maxLen);
                if ((int)s.size() < cfg_.minLen) {
                    s += randomFixedLen(cfg_.minLen - (int)s.size());
                }
                a.push_back(std::move(s));
            }
            return a;
        }
    
    private:
        Config cfg_;
        mt19937_64 rng_;
        string randomFixedLen(int len) {
            uniform_int_distribution<int> chDist(0, (int)alphabet().size() - 1);
            string s;
            s.reserve(len);
            for (int i = 0; i < len; ++i) s.push_back(alphabet()[chDist(rng_)]);
            return s;
        }
    };

    