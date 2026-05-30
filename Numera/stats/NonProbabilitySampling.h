#ifndef NON_PROBABILITY_SAMPLIG_H
#define NON_PROBABILITY_SAMPLIG_H

#include<vector>
#include<random>
#include<algorithm>
#include <chrono>
#include <unordered_map>
#include<iostream>
#include<cmath>
#include "DataModel/NumericSample.h"

namespace nr
{
    /*
        Functions for finding non-probability samples are declared here.
    */
    class NonProbabilitySampling
    {
    public:

        NonProbabilitySampling() = delete;

        template<typename DataContainer, typename LabelContainer>
        static auto quotaSample(
            const DataContainer& data,
            const LabelContainer& labels,
            const std::unordered_map<size_t, size_t>& quotas)
        -> std::vector<typename DataContainer::value_type>;
            
        template<typename Container>
        static auto haphazardSample(
            const Container& data, 
            size_t sampleSize)
        -> std::vector<typename Container::value_type>;

        template<typename Container>
        static auto convenienceSample(
            const Container& data, 
            size_t sampleSize)
        -> std::vector<typename Container::value_type>;

        //////////////////////////////////////////////////////////////////

        template<typename IteratorData, typename IteratorLabels>
        static auto quotaSample(
            const IteratorData data_begin,
            const IteratorData data_end,
            const IteratorLabels labels_begin,
            const std::unordered_map<size_t, size_t>& quotas)
        -> std::vector<typename std::iterator_traits<IteratorData>::value_type>;
            
        template<typename Iterator>
        static auto haphazardSample(
            const Iterator begin,
            const Iterator end, 
            size_t sampleSize)
        -> std::vector<typename std::iterator_traits<Iterator>::value_type>;

        template<typename Iterator>
        static auto convenienceSample(
            const Iterator begin,
            const Iterator end,
            size_t sampleSize)
        -> std::vector<typename std::iterator_traits<Iterator>::value_type>;
    };

    template <typename DataContainer, typename LabelContainer>
    inline auto NonProbabilitySampling::quotaSample(
        const DataContainer &data, 
        const LabelContainer &labels, 
        const std::unordered_map<size_t, size_t> &quotas)
    -> std::vector<typename DataContainer::value_type>
    {
        /*
            In the current function,
             use only sequential containers as the data parameter!
        */
        using T = typename DataContainer::value_type;

        static_assert(
        std::is_same_v<
            typename LabelContainer::value_type,
            size_t>,
        "Labels must contain size_t values");

        // Quota sampling
        if (std::begin(data) == std::end(data) || std::size(data) != std::size(labels) || quotas.empty())
        {
            return {};
        }

        std::vector<T> out;

        std::unordered_map<size_t, std::vector<T>> groups;

        auto data_it = std::begin(data);
        auto label_it = std::begin(labels);

        for (; data_it != std::end(data); ++data_it, ++label_it) {
            groups[*label_it].push_back(*data_it);;
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

    template <typename Container>
    inline auto NonProbabilitySampling::haphazardSample(
        const Container &data, 
        size_t sampleSize) 
    -> std::vector<typename Container::value_type>
    {
        /*
            In the current function,
             use only sequential containers as the data parameter!
        */

        // Spontaneous sampling
        using T = typename Container::value_type;


        if (std::begin(data) == std::end(data) || sampleSize == 0) 
        {
            return {};
        }

        std::vector<T> shuffled(std::begin(data), std::end(data));

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

    template <typename Container>
    inline auto NonProbabilitySampling::convenienceSample(
        const Container &data, 
        size_t sampleSize) 
    -> std::vector<typename Container::value_type>
    {
        /*
            In the current function,
             use only sequential containers as the data parameter!
        */
       
        // Convenient selection
        using T = typename Container::value_type;

        if (std::begin(data) == std::end(data) || sampleSize == 0)
            return {};

        std::vector<T> out;
        out.reserve(sampleSize);
        auto data_it = std::begin(data);

        auto data_size = std::distance(std::begin(data), std::end(data));

        // We take elements based on availability (the first sampleSize of elements)
        for (size_t i = 0; i < data_size && out.size() < sampleSize && data_it != std::end(data); ++i, ++data_it)
        {
            out.push_back(*data_it);
        }

        return out;
    }

    template <typename IteratorData, typename IteratorLabels>
    inline auto NonProbabilitySampling::quotaSample(
        const IteratorData data_begin, 
        const IteratorData data_end,
        const IteratorLabels labels_begin, 
        const std::unordered_map<size_t, size_t> &quotas) 
    -> std::vector<typename std::iterator_traits<IteratorData>::value_type>
    {
        /*
            In the current function,
             use only sequential containers as the data parameter!
        */
        using T_data = typename std::iterator_traits<IteratorData>::value_type;
        using T_label = typename std::iterator_traits<IteratorLabels>::value_type;

        static_assert(
        std::is_same_v<T_label, size_t>,
        "Labels must contain size_t values");

        // Quota sampling
        if (data_begin == data_end || quotas.empty())
        {
            return {};
        }

        std::vector<T_data> out;

        std::unordered_map<size_t, std::vector<T_data>> groups;

        auto data_it = data_begin;
        auto label_it = labels_begin;

        for (; data_it != data_end; ++data_it, ++label_it) {
            groups[*label_it].push_back(*data_it);;
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
    template <typename Iterator>
    inline auto NonProbabilitySampling::haphazardSample(
        const Iterator begin, 
        const Iterator end, 
        size_t sampleSize) 
    -> std::vector<typename std::iterator_traits<Iterator>::value_type>
    {
        /*
            In the current function,
             use only sequential containers as the data parameter!
        */

        // Spontaneous sampling
        using T = typename std::iterator_traits<Iterator>::value_type;


        if (begin == end || sampleSize == 0) 
        {
            return {};
        }

        std::vector<T> shuffled(begin, end);

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
    template <typename Iterator>
    inline auto NonProbabilitySampling::convenienceSample(
        const Iterator begin, 
        const Iterator end, 
        size_t sampleSize) 
    -> std::vector<typename std::iterator_traits<Iterator>::value_type>
    {
        using T = typename std::iterator_traits<Iterator>::value_type;

        /*
            In the current function,
             use only sequential containers as the data parameter!
        */
       
        // Convenient selection

        if (begin == end || sampleSize == 0)
            return {};

        std::vector<T> out;
        out.reserve(sampleSize);
        auto data_it = begin;

        auto data_size = std::distance(begin, end);

        // We take elements based on availability (the first sampleSize of elements)
        for (size_t i = 0; i < data_size && out.size() < sampleSize && data_it != end; ++i, ++data_it)
        {
            out.push_back(*data_it);
        }

        return out;
    }
}

#endif //NON_PROBABILITY_SAMPLIG_H