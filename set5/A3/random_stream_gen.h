#pragma once
#include <bits/stdc++.h>

class RandomStreamGen {
public:
    struct Config {
        size_t stream_len = 100000;  // длина потока (колво строк)
        size_t max_str_len = 30;  // макс длина строки
        uint64_t seed = 1;    // seed генератора
        int step_percent = 5;   // шаг времени (5% - 20 точек)
    };

    explicit RandomStreamGen(Config cfg)
        : cfg_(cfg), rng_(cfg.seed) {}

    // Сгенерировать поток S
    std::vector<std::string> generate_stream() {
        std::vector<std::string> s;
        s.reserve(cfg_.stream_len);
        for (size_t i = 0; i < cfg_.stream_len; ++i) {
            s.push_back(gen_string());
        }
        return s;
    }

    // Вернуть список размеров префиксов потока, соответствующих моментам времени t
    std::vector<size_t> prefix_sizes() const {
        std::vector<size_t> pref;
        int step = std::max(1, cfg_.step_percent);
        for (int p = step; p <= 100; p += step) {
            size_t len = (cfg_.stream_len * (size_t)p) / 100;
            if (len == 0) len = 1;
            pref.push_back(len);
        }
        if (pref.empty() || pref.back() != cfg_.stream_len) pref.push_back(cfg_.stream_len);
        // уберём дубликаты 
        pref.erase(std::unique(pref.begin(), pref.end()), pref.end());
        return pref;
    }

private:
    Config cfg_;
    std::mt19937_64 rng_;

    static constexpr const char* alphabet_ =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789-";

    std::string gen_string() {
        std::uniform_int_distribution<int> len_dist(1, (int)cfg_.max_str_len);
        std::uniform_int_distribution<int> ch_dist(0, (int)std::strlen(alphabet_) - 1);

        int len = len_dist(rng_);
        std::string out;
        out.reserve((size_t)len);
        for (int i = 0; i < len; ++i) {
            out.push_back(alphabet_[ch_dist(rng_)]);
        }
        return out;
    }
};