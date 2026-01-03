#ifndef PROBABILITY_SAMPLING_H
#define PROBABILITY_SAMPLING_H
#include "RandomGenerator/RandomValueGenerator.h"

#include<vector>
#include<random>
#include<algorithm>
#include <chrono>
#include <unordered_map>
#include<iostream>
#include<cmath>
#include "Core/NumericSample.h"

namespace nr
{
    /*
        Functions for finding probability samples are declared here.
    */
    class ProbabilitySampling {
    public:
        template<typename T>
        static std::vector<T> simple_random(
            const std::vector<T>& data,
            size_t sampleSize);

        template<typename T>
        static std::vector<T> systematic(
            const std::vector<T>& data,
            size_t sample);

        template<typename T>
        static std::vector<T> stratified(
            const std::vector<T>& data,
            const std::vector<size_t>& strataLabels,
            size_t sampleSize);

////////////////////////////////////////////////////
        template<typename T>
        static std::vector<T> simple_random(
            const nr::NumericSample<T>& data,
            size_t sampleSize);

        template<typename T>
        static std::vector<T> systematic(
            const nr::NumericSample<T>& data,
            size_t sample);

        template<typename T>
        static std::vector<T> stratified(
            const nr::NumericSample<T>& data,
            const std::vector<size_t>& strataLabels,
            size_t sampleSize);
    };

    template<typename T>
    std::vector<T> ProbabilitySampling::simple_random(
        const std::vector<T>& data,
        size_t sampleSize)
    {
        // Simple random sampling
        if (sampleSize == 0 || data.empty()) return {};

        // Use a thread-local generator seeded once per thread with mixed entropy.
        auto &gen = nr::RandomValueGenerator::get_thread_local_generator();

        size_t size = std::min(sampleSize, data.size());

        std::vector<double> out;
        out.reserve(size);

        std::sample(data.begin(), data.end(), std::back_inserter(out),
                    size, gen);
        
        std::shuffle(out.begin(), out.end(), gen);

        return out;
    }

    template<typename T>
    std::vector<T> ProbabilitySampling::systematic(
        const std::vector<T>& data,
        size_t sample)
    {
        //Systematic sampling

        // requires a sorted population
        if (data.empty() || sample == 0) return {};

        auto population = data;

        size_t n = population.size();
        size_t start = 0;
        size_t step = n / sample;
        if (step > 1) 
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<size_t> dist(0, std::min(step, n) - 1);
            start = dist(gen);
        }

        std::vector<double> out;
        out.reserve((n + step - 1) / step);

        for (size_t i = start; i < n; i += step) {
            out.push_back(population[i++]);
        }

        return out;
    }

    template<typename T>
    std::vector<T> ProbabilitySampling::stratified(
        const std::vector<T>& data,
        const std::vector<size_t>& strataLabels,
        size_t sampleSize)
    {
        // Stratified sampling

        if (data.empty() || strataLabels.size() != data.size() || sampleSize == 0) return {};

        size_t dataSize = data.size();

        // Grouping indices by strata
        std::unordered_map<size_t, std::vector<size_t>> groups;
        for (size_t i = 0; i < strataLabels.size(); ++i) 
        {
            groups[strataLabels[i]].push_back(i);
        }

        // A vector to store the target size k for each stratum and its fractional remainder
        std::vector<std::pair<double, size_t>> fractional_targets; // {fractional remainder, stratum mark}
        std::unordered_map<size_t, size_t> final_k_values; // {stratum label, final size k}
        size_t total_picked_so_far = 0;

        for (auto const& [label, idxs] : groups) 
        {
            // Calculating the size of k using floating point
            double target_k_double = (static_cast<double>(idxs.size()) * sampleSize) / dataSize;
            
            // Base size k - round down (integer part)
            size_t base_k = static_cast<size_t>(std::floor(target_k_double));

            // Guarantee that a small stratum selects at least 1 element if it is not empty
            if (base_k == 0 && idxs.size() > 0) 
            {
                base_k = 1;
            }

            // We calculate the fractional remainder for the distribution of missing elements
            double fraction = target_k_double - base_k;
            
            // We write down the base value
            final_k_values[label] = base_k;
            total_picked_so_far += base_k;

            // Save the remainder and the stratum label
            fractional_targets.push_back({fraction, label});
        }

        // Calculation of missing elements (the remainder to be distributed)
        size_t remainder = 0;
        if (sampleSize > total_picked_so_far) 
        {
            remainder = sampleSize - total_picked_so_far;
        }
        
        // Sort by descending fractional remainder
        // The strata with the largest remainder will receive additional missing elements
        std::sort(fractional_targets.begin(), fractional_targets.end(), [](const auto& a, const auto& b) {
            return a.first > b.first; 
        });

        // Distribution of missing elements
        for (size_t i = 0; i < remainder; ++i) 
        {
            size_t label_to_increase = fractional_targets[i].second;
            final_k_values[label_to_increase]++;
        }

        // --- FORMATION OF THE FINAL SAMPLE ---

        std::vector<double> out;
        out.reserve(sampleSize); 
        auto &gen = nr::RandomValueGenerator::get_thread_local_generator();

        for (auto const& [label, idxs] : groups) 
        {
            size_t k = final_k_values.at(label); // We get the EXACTLY calculated k
            
            // We guarantee that k does not exceed the size of the stratum
            k = std::min(k, idxs.size()); 

            std::vector<size_t> picked;
            picked.reserve(k);
            // We use std::sample
            std::sample(idxs.begin(), idxs.end(), std::back_inserter(picked), k, gen);

            for (auto id : picked) out.push_back(data[id]);
        }

        // Mixing
        std::shuffle(out.begin(), out.end(), gen);
        return out;
    }

    template<typename T>
    std::vector<T> ProbabilitySampling::simple_random(
        const nr::NumericSample<T>& data,
        size_t sampleSize)
    {
        // Simple random sampling

        if (sampleSize == 0 || data.empty()) return {};

        // Use a thread-local generator seeded once per thread with mixed entropy.
        auto &gen = nr::RandomValueGenerator::get_thread_local_generator();

        size_t size = std::min(sampleSize, data.size());

        std::vector<double> out;
        out.reserve(size);

        std::sample(data.cbegin(), data.cend(), std::back_inserter(out),
                    size, gen);
        
        std::shuffle(out.begin(), out.end(), gen);

        return out;
    }

    template<typename T>
    std::vector<T> ProbabilitySampling::systematic(
        const nr::NumericSample<T>& data,
        size_t sample)
    {
        //Systematic sampling
        if (data.empty() || sample == 0) return {};
        auto population = std::vector<double>(data.cbegin(), data.cend());
        std::sort(population.begin(), population.end());

        size_t n = population.size();
        size_t start = 0;
        size_t step = n / sample;
        if (step > 1) 
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<size_t> dist(0, std::min(step, n) - 1);
            start = dist(gen);
        }

        std::vector<double> out;
        out.reserve((n + step - 1) / step);

        for (size_t i = start; i < n; i += step) 
        {
            out.push_back(population[i++]);
        }

        return out;
    }

    template<typename T>
    std::vector<T> ProbabilitySampling::stratified(
        const nr::NumericSample<T>& data,
        const std::vector<size_t>& strataLabels,
        size_t sampleSize)
    {
        // Stratified sampling

        if (data.empty() || strataLabels.size() != data.size() || sampleSize == 0) return {};

        size_t dataSize = data.size();

        // Grouping indices by strata
        std::unordered_map<size_t, std::vector<size_t>> groups;
        for (size_t i = 0; i < strataLabels.size(); ++i) 
        {
            groups[strataLabels[i]].push_back(i);
        }

        // A vector to store the target size k for each stratum and its fractional remainder
        std::vector<std::pair<double, size_t>> fractional_targets; // {fractional remainder, stratum mark}
        std::unordered_map<size_t, size_t> final_k_values; // {stratum label, final size k}
        size_t total_picked_so_far = 0;

        for (auto const& [label, idxs] : groups) 
        {
            // Calculating the size of k using floating point
            double target_k_double = (static_cast<double>(idxs.size()) * sampleSize) / dataSize;
            
            // Base size k - round down (integer part)
            size_t base_k = static_cast<size_t>(std::floor(target_k_double));

            // Guarantee that a small stratum selects at least 1 element if it is not empty
            if (base_k == 0 && idxs.size() > 0) 
            {
                base_k = 1;
            }

            // We calculate the fractional remainder for the distribution of missing elements
            double fraction = target_k_double - base_k;
            
            // We write down the base value
            final_k_values[label] = base_k;
            total_picked_so_far += base_k;

            // Save the remainder and the stratum label
            fractional_targets.push_back({fraction, label});
        }

        // Calculation of missing elements (the remainder to be distributed)
        size_t remainder = 0;
        if (sampleSize > total_picked_so_far) 
        {
            remainder = sampleSize - total_picked_so_far;
        }
        
        // Sort by descending fractional remainder
        // The strata with the largest remainder will receive additional missing elements
        std::sort(fractional_targets.begin(), fractional_targets.end(), [](const auto& a, const auto& b) {
            return a.first > b.first; 
        });

        // Distribution of missing elements
        for (size_t i = 0; i < remainder; ++i) 
        {
            size_t label_to_increase = fractional_targets[i].second;
            final_k_values[label_to_increase]++;
        }

        // --- FORMATION OF THE FINAL SAMPLE ---

        std::vector<double> out;
        out.reserve(sampleSize); 
        auto &gen = nr::RandomValueGenerator::get_thread_local_generator();

        for (auto const& [label, idxs] : groups) 
        {
            size_t k = final_k_values.at(label); // We get the EXACTLY calculated k
            
            // We guarantee that k does not exceed the size of the stratum
            k = std::min(k, idxs.size()); 

            std::vector<size_t> picked;
            picked.reserve(k);
            // We use std::sample
            std::sample(idxs.begin(), idxs.end(), std::back_inserter(picked), k, gen);

            for (auto id : picked) out.push_back(data[id]);
        }

        // Mixing
        std::shuffle(out.begin(), out.end(), gen);
        return out;
    }
}

#endif // PROBABILITY_SAMPLING_H