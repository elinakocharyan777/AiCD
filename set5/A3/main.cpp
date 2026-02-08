#include <bits/stdc++.h>
#include "random_stream_gen.h"
#include "hash_func_gen.h"

using namespace std;

class HyperLogLog {
public:
    HyperLogLog(int B, const HashFuncGen& hf) : B_(B), hf_(hf) {
        if (B_ < 4 || B_ > 16) {
            throw runtime_error("B should be in [4..16] for this lab setup");
        }
        m_ = 1u << B_;
        regs_.assign(m_, 0);
        alpha_ = alpha_m(m_);
    }

    void reset() { std::fill(regs_.begin(), regs_.end(), 0); }

    void add(const string& s) {
        uint32_t x = hf_.hash32(s);

        // index = первые B битов
        uint32_t idx = x >> (32 - B_);
        uint32_t w = (x << B_);
    
        int lz = 0;
        if (w == 0) {
            lz = 32; 
        } else {
            lz = __builtin_clz(w);
        }
        int rho = lz + 1;
        regs_[idx] = (uint8_t)max<int>(regs_[idx], rho);
    }

    double estimate() const {
        double sum = 0.0;
        for (uint8_t v : regs_) {
            sum += std::ldexp(1.0, -(int)v); // 2^-v
        }
        double E = alpha_ * (double)m_ * (double)m_ / sum;
        return E;
    }

private:
    int B_;
    uint32_t m_;
    double alpha_;
    const HashFuncGen& hf_;
    vector<uint8_t> regs_;

    static double alpha_m(uint32_t m) {
        if (m == 16) return 0.673;
        if (m == 32) return 0.697;
        if (m == 64) return 0.709;
        return 0.7213 / (1.0 + 1.079 / (double)m);
    }
};

//точный счёт F0^t 
static size_t exact_unique_prefix(const vector<string>& stream, size_t pref_len) {
    unordered_set<string> st;
    st.reserve(pref_len * 2);
    for (size_t i = 0; i < pref_len; ++i) st.insert(stream[i]);
    return st.size();
}

// mean & std 
static pair<double,double> mean_std(const vector<double>& xs) {
    double mean = 0.0;
    for (double x : xs) mean += x;
    mean /= (double)xs.size();

    double var = 0.0;
    for (double x : xs) var += (x - mean) * (x - mean);
    var /= (double)xs.size();
    double sd = sqrt(var);
    return {mean, sd};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // настройки эксперимента 
    const int R = 30;   // число потоков (для статистики)
    const int B =12;    // параметр HLL, m=2^B 
    const uint64_t base_seed = 42; // общий seed

    RandomStreamGen::Config cfg;
    cfg.stream_len = 100000;  // длина потока
    cfg.max_str_len = 30;
    cfg.step_percent = 5;  // 5% => 20 точек времени

    // hash generator
    HashFuncGen hf(0x123456789ABCDEF0ULL);

    // список префиксов (t)
    RandomStreamGen tmp(cfg);
    vector<size_t> pref = tmp.prefix_sizes();
    const int T = (int)pref.size();

    //для каждого t точное F0^t и оценки Nt по потокам - mean/sd
    vector<vector<double>> Nt_samples(T); 
    vector<vector<double>> F0_samples(T); 

    for (int r = 0; r < R; ++r) {
        cfg.seed = base_seed + (uint64_t)r * 99991ULL;
        RandomStreamGen gen(cfg);
        vector<string> stream = gen.generate_stream();

        HyperLogLog hll(B, hf);
        hll.reset();

        unordered_set<string> exact_set;
        exact_set.reserve(cfg.stream_len * 2);

        size_t next_t_idx = 0;
        for (size_t i = 0; i < stream.size(); ++i) {
            hll.add(stream[i]);
            exact_set.insert(stream[i]);

            size_t processed = i + 1;
            while (next_t_idx < pref.size() && processed == pref[next_t_idx]) {
                double Nt = hll.estimate();
                double F0 = (double)exact_set.size();

                Nt_samples[next_t_idx].push_back(Nt);
                F0_samples[next_t_idx].push_back(F0);

                next_t_idx++;
            }
            if (next_t_idx >= pref.size()) break;
        }
    }

    // Вывод CSV для графиков (t_step, processed, F0_mean, Nt_mean, Nt_sd, Nt_mean-Nt_sd, Nt_mean+Nt_sd) 
    cout << "step,processed,F0_mean,Nt_mean,Nt_sd,Nt_minus_sd,Nt_plus_sd\n";

    for (int ti = 0; ti < T; ++ti) {
        auto [Nt_mean, Nt_sd] = mean_std(Nt_samples[ti]);
        auto [F0_mean, F0_sd] = mean_std(F0_samples[ti]); // sd можем не выводить

        double minus_sd = Nt_mean - Nt_sd;
        double plus_sd  = Nt_mean + Nt_sd;

        cout << ti
             << "," << pref[ti]
             << "," << fixed << setprecision(6) << F0_mean
             << "," << fixed << setprecision(6) << Nt_mean
             << "," << fixed << setprecision(6) << Nt_sd
             << "," << fixed << setprecision(6) << minus_sd
             << "," << fixed << setprecision(6) << plus_sd
             << "\n";
    }
    return 0;
}