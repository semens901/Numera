#include "randomValueGenerator.h"

std::mt19937_64 &nr::RandomValueGenerator::get_thread_local_generator()
{
    auto &gen = []() -> std::mt19937_64& {
        static thread_local std::mt19937_64 g = [](){
            std::random_device rd;
            std::vector<uint32_t> seeds;
            seeds.reserve(8);
            auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            for (int i = 0; i < 8; ++i) {
                seeds.push_back(rd() ^ static_cast<uint32_t>((now >> (i * 8)) & 0xFFFFFFFFu));
            }
            std::seed_seq seq(seeds.begin(), seeds.end());
            return std::mt19937_64(seq);
        }();
        return g;
    }();
    return gen;
}
