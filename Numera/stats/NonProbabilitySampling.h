#ifndef NON_PROBABILITY_SAMPLIG_H
#define NON_PROBABILITY_SAMPLIG_H

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
        Functions for finding non-probability samples are declared here.
    */
    class NonProbabilitySampling
    {
    public:

        NonProbabilitySampling() = delete;

        template<typename T>
        static std::vector<T> quotaSample(
            const std::vector<T>& data,
            const std::vector<size_t>& labels,             // group labels for each element
            const std::unordered_map<size_t, size_t>& quotas);
            
        template<typename T>
        static std::vector<T> haphazardSample(
            const std::vector<T>& data, 
            size_t sampleSize);

        template<typename T>
        static std::vector<T> convenienceSample(
            const std::vector<T>& data, 
            size_t sampleSize);
    ///////////////////////////////////////////////////////
        template<typename T>
        static NumericSample<T> quotaSample(
            const nr::NumericSample<T>& data,
            const std::vector<size_t>& labels,             // group labels for each element
            const std::unordered_map<size_t, size_t>& quotas);
            
        template<typename T>
        static NumericSample<T> haphazardSample(
            const nr::NumericSample<T>& data, 
            size_t sampleSize);
            
        template<typename T>
        static NumericSample<T> convenienceSample(
            const nr::NumericSample<T>& data, 
            size_t sampleSize);
    };

    template <typename T>
    inline std::vector<T> NonProbabilitySampling::quotaSample(const std::vector<T> &data, const std::vector<size_t> &labels, const std::unordered_map<size_t, size_t> &quotas)
    {
        // Quota sampling
        if (data.empty() || labels.size() != data.size() || quotas.empty())
            return {};

        std::vector<T> out;

        std::unordered_map<size_t, std::vector<T>> groups;
        for (size_t i = 0; i < data.size(); ++i) {
            groups[labels[i]].push_back(data[i]);
        }

        for (const auto& [label, vec] : groups) {
            auto it = quotas.find(label);
            if (it == quotas.end() || vec.empty())
                continue;

            size_t k = std::min(it->second, vec.size()); // quota no more than available items

            for (size_t i = 0; i < k; ++i)
                out.push_back(vec[i]);
        }

        return out;
    }

    template <typename T>
    inline std::vector<T> NonProbabilitySampling::haphazardSample(const std::vector<T> &data, size_t sampleSize)
    {
        // Spontaneous sampling
        if (data.empty() || sampleSize == 0) 
        {
            return {};
        }

        std::vector<T> shuffled = data;

        // Non-deterministic source
        std::mt19937 gen(std::random_device{}());
        std::shuffle(shuffled.begin(), shuffled.end(), gen);

        if (sampleSize >= shuffled.size()) 
        {
            return shuffled;
        }

        return std::vector<T>(
            shuffled.begin(),
            shuffled.begin() + sampleSize
        );
    }

    template <typename T>
    inline std::vector<T> NonProbabilitySampling::convenienceSample(const std::vector<T> &data, size_t sampleSize)
    {
        // Convenient selection
        if (data.empty() || sampleSize == 0)
            return {};

        std::vector<T> out;
        out.reserve(sampleSize);

        // We take elements based on availability (the first sampleSize of elements)
        for (size_t i = 0; i < data.size() && out.size() < sampleSize; ++i)
        {
            out.push_back(data[i]);
        }

        return out;
    }

    template <typename T>
    inline nr::NumericSample<T> NonProbabilitySampling::quotaSample(const nr::NumericSample<T> &data, const std::vector<size_t> &labels, const std::unordered_map<size_t, size_t> &quotas)
    {
        // Quota sampling
        if (data.empty() || labels.size() != data.size() || quotas.empty())
            return {};

        nr::NumericSample<T> out;

        // First, we collect the elements into groups
        std::unordered_map<size_t, std::vector<T>> groups;
        for (size_t i = 0; i < data.size(); ++i) {
            groups[labels[i]].push_back(data[i]);
        }

        // For each group we take elements according to the quota
        for (const auto& [label, vec] : groups) {
            auto it = quotas.find(label);
            if (it == quotas.end() || vec.empty())
                continue;

            size_t k = std::min(it->second, vec.size()); // quota no more than available items

            for (size_t i = 0; i < k; ++i)
                out.push_back(vec[i]);
        }

        return out;
    }

    template <typename T>
    inline nr::NumericSample<T> NonProbabilitySampling::haphazardSample(const nr::NumericSample<T> &data, size_t sampleSize)
    {
        // Spontaneous sampling
        if (data.empty() || sampleSize == 0) 
        {
            return {};
        }

        nr::NumericSample<T> shuffled = data;

        // Non-deterministic source
        std::mt19937 gen(std::random_device{}());
        std::shuffle(shuffled.begin(), shuffled.end(), gen);

        if (sampleSize >= shuffled.size()) 
        {
            return shuffled;
        }

        return nr::NumericSample<T>(
            shuffled.begin(),
            shuffled.begin() + sampleSize
        );
    }

    template <typename T>
    inline nr::NumericSample<T> NonProbabilitySampling::convenienceSample(const nr::NumericSample<T> &data, size_t sampleSize)
    {
        // Convenient selection
        if (data.empty() || sampleSize == 0)
            return {};

        nr::NumericSample<T> out;
        out.reserve(sampleSize);

        // We take elements based on availability (the first sampleSize of elements)
        for (size_t i = 0; i < data.size() && out.size() < sampleSize; ++i)
        {
            out.push_back(data[i]);
        }

        return out;
    }

}

#endif //NON_PROBABILITY_SAMPLIG_H