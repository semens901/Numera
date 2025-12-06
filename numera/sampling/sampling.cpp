#include "sampling.h"
#include <chrono>
#include <unordered_map>

std::vector<double> nr::Sampling::simple_random(const std::vector<double> &data, size_t sampleSize)
{
    if (sampleSize == 0 || data.empty()) return {};

    // Use a thread-local generator seeded once per thread with mixed entropy.
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

    size_t size = std::min(sampleSize, data.size());

    std::vector<double> out;
    out.reserve(size);

    std::sample(data.begin(), data.end(), std::back_inserter(out),
                size, gen);
    
    std::shuffle(out.begin(), out.end(), gen);

    return out;
}

std::vector<double> nr::Sampling::systematic(const std::vector<double> &data, size_t step)
{
    // requires a sorted population
    if (data.empty() || step == 0) return {};

    auto population = data;

    size_t n = population.size();
    size_t start = 0;
    if (step > 1) {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<size_t> dist(0, std::min(step, n) - 1);
        start = dist(gen);
    }

    std::vector<double> out;
    out.reserve((n + step - 1) / step);

    for (size_t i = start; i < n; i += step) {
        out.push_back(population[i]);
    }

    return out;
}

std::vector<double> nr::Sampling::systematic_sorted(const std::vector<double> &data, size_t step)
{
    if (data.empty() || step == 0) return {};

    auto population = data;
    std::sort(population.begin(), population.end());

    size_t n = population.size();
    size_t start = 0;
    if (step > 1) {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<size_t> dist(0, std::min(step, n) - 1);
        start = dist(gen);
    }

    std::vector<double> out;
    out.reserve((n + step - 1) / step);

    for (size_t i = start; i < n; i += step) {
        out.push_back(population[i]);
    }

    return out;
}

std::vector<double> nr::Sampling::stratified(const std::vector<double> &data, const std::vector<size_t> &strataLabels, size_t samplePerStratum)
{
    if (data.empty()) return {};
    if (strataLabels.size() != data.size()) return {};
    if (samplePerStratum == 0) return {};

    // Group indices by strata label (do not copy values)
    std::unordered_map<size_t, std::vector<size_t>> groups;
    groups.reserve(16);
    for (size_t i = 0; i < strataLabels.size(); ++i) {
        groups[strataLabels[i]].push_back(i);
    }

    std::vector<double> out;
    out.reserve(groups.size() * samplePerStratum);

    // get same thread-local generator as used elsewhere
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

    for (auto &kv : groups) {
        auto &idxs = kv.second;
        size_t k = std::min(samplePerStratum, idxs.size());
        if (k == 0) continue;

        std::vector<size_t> picked;
        picked.reserve(k);
        std::sample(idxs.begin(), idxs.end(), std::back_inserter(picked), k, gen);

        for (auto id : picked) out.push_back(data[id]);
    }

    // optional: shuffle across strata to avoid block ordering
    std::shuffle(out.begin(), out.end(), gen);
    return out;
}

///////////////////////////////////////////////

std::vector<double> nr::Sampling::simple_random(const Numera &data, size_t sampleSize)
{
    return std::vector<double>();
}

std::vector<double> nr::Sampling::systematic(const Numera &data, size_t step)
{
    return std::vector<double>();
}

std::vector<double> nr::Sampling::stratified(const Numera &data, const std::vector<size_t> &strataLabels, size_t samplePerStratum)
{
    return std::vector<double>();
}
