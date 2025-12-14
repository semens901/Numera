#ifndef NON_PROBABILITY_SAMPLIG_H
#define NON_PROBABILITY_SAMPLIG_H

#include<vector>
#include<random>
#include<algorithm>
#include <chrono>
#include <unordered_map>
#include<iostream>
#include<cmath>
#include "Core/VectorData.h"
#include "Core/CsvData.h"

namespace nr
{
    class NonProbabilitySampling
    {
    public:
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
        static VectorData<T> quotaSample(
            const nr::VectorData<T>& data,
            const std::vector<size_t>& labels,             // group labels for each element
            const std::unordered_map<size_t, size_t>& quotas);
            
        template<typename T>
        static VectorData<T> haphazardSample(
            const nr::VectorData<T>& data, 
            size_t sampleSize);
            
        template<typename T>
        static VectorData<T> convenienceSample(
            const nr::VectorData<T>& data, 
            size_t sampleSize);
///////////////////////////////////////////////////////
        template<typename KEY_T, typename Value_T>
        static nr::VectorData<Value_T> quotaSample(
        const nr::CSVDataStore<KEY_T, Value_T>& data, 
        const std::unordered_map<KEY_T, size_t>& quotas);
        
        template<typename KEY_T, typename Value_T>
        static nr::VectorData<Value_T> haphazardSample(
            const nr::CSVDataStore<KEY_T, Value_T>& data, 
            size_t sampleSize);

        template<typename KEY_T, typename Value_T>
        static nr::VectorData<Value_T> convenienceSample(
            const nr::CSVDataStore<KEY_T, Value_T>& data, 
            size_t sampleSize);
    };
}
template <typename T>
inline std::vector<T> nr::NonProbabilitySampling::quotaSample(const std::vector<T> &data, const std::vector<size_t> &labels, const std::unordered_map<size_t, size_t> &quotas)
{
    if (data.empty() || labels.size() != data.size() || quotas.empty())
        return {};

    std::vector<T> out;

    // Сначала собираем элементы по группам
    std::unordered_map<size_t, std::vector<T>> groups;
    for (size_t i = 0; i < data.size(); ++i) {
        groups[labels[i]].push_back(data[i]);
    }

    // Для каждой группы берём элементы по квоте
    for (const auto& [label, vec] : groups) {
        auto it = quotas.find(label);
        if (it == quotas.end() || vec.empty())
            continue;

        size_t k = std::min(it->second, vec.size()); // квота не больше доступных элементов

        for (size_t i = 0; i < k; ++i)
            out.push_back(vec[i]);
    }

    return out;
}

template <typename T>
inline std::vector<T> nr::NonProbabilitySampling::haphazardSample(const std::vector<T> &data, size_t sampleSize)
{
    if (data.empty() || sampleSize == 0)
        return {};

    std::vector<T> out;
    out.reserve(sampleSize);

    // Берём элементы по порядку до sampleSize
    for (size_t i = 0; i < data.size() && out.size() < sampleSize; ++i)
    {
        out.push_back(data[i]);
    }

    return out; // если sampleSize больше, чем элементов — возвращаем все
}

template <typename T>
inline std::vector<T> nr::NonProbabilitySampling::convenienceSample(const std::vector<T> &data, size_t sampleSize)
{
    if (data.empty() || sampleSize == 0)
        return {};

    std::vector<T> out;
    out.reserve(sampleSize);

    // Берём элементы по доступности (первые sampleSize элементов)
    for (size_t i = 0; i < data.size() && out.size() < sampleSize; ++i)
    {
        out.push_back(data[i]);
    }

    return out; // если sampleSize больше количества элементов — возвращаем все
}

template <typename T>
inline nr::VectorData<T> nr::NonProbabilitySampling::quotaSample(const nr::VectorData<T> &data, const std::vector<size_t> &labels, const std::unordered_map<size_t, size_t> &quotas)
{
    if (data.empty() || labels.size() != data.size() || quotas.empty())
        return {};

    nr::VectorData<T> out;

    // Сначала собираем элементы по группам
    std::unordered_map<size_t, std::vector<T>> groups;
    for (size_t i = 0; i < data.size(); ++i) {
        groups[labels[i]].push_back(data[i]);
    }

    // Для каждой группы берём элементы по квоте
    for (const auto& [label, vec] : groups) {
        auto it = quotas.find(label);
        if (it == quotas.end() || vec.empty())
            continue;

        size_t k = std::min(it->second, vec.size()); // квота не больше доступных элементов

        for (size_t i = 0; i < k; ++i)
            out.push_back(vec[i]);
    }

    return out;
}

template <typename T>
inline nr::VectorData<T> nr::NonProbabilitySampling::haphazardSample(const nr::VectorData<T> &data, size_t sampleSize)
{
    if (data.empty() || sampleSize == 0)
        return {};

    nr::VectorData<T> out;
    //out.reserve(sampleSize);

    // Берём элементы по порядку до sampleSize
    for (size_t i = 0; i < data.size() && out.size() < sampleSize; ++i)
    {
        out.push_back(data[i]);
    }

    return out; // если sampleSize больше, чем элементов — возвращаем все
}

template <typename T>
inline nr::VectorData<T> nr::NonProbabilitySampling::convenienceSample(const nr::VectorData<T> &data, size_t sampleSize)
{
    if (data.empty() || sampleSize == 0)
        return {};

    std::vector<T> out;
    out.reserve(sampleSize);

    // Берём элементы по доступности (первые sampleSize элементов)
    for (size_t i = 0; i < data.size() && out.size() < sampleSize; ++i)
    {
        out.push_back(data[i]);
    }

    return out; // если sampleSize больше количества элементов — возвращаем все
}

template <typename KEY_T, typename Value_T>
inline nr::VectorData<Value_T> nr::NonProbabilitySampling::quotaSample(
    const nr::CSVDataStore<KEY_T, Value_T> &data,
    const std::unordered_map<KEY_T, size_t> &quotas)
{
    if (data.empty() || quotas.empty())
        return {};

    nr::VectorData<Value_T> out;

    for (const auto& [label, values] : data)
    {
        // We check if there is a quota for this group
        auto it = quotas.find(label);
        if (it == quotas.end() || values.empty())
            continue;

        size_t k = it->second;             // Quota for this group
        k = std::min(k, values.size());    // We do not exceed the available quantity

        // We take the first k elements from values
        for (size_t i = 0; i < k; ++i)
            out.push_back(values[i]);
    }

    return out;
}

template <typename KEY_T, typename Value_T>
inline nr::VectorData<Value_T> nr::NonProbabilitySampling::haphazardSample(const nr::CSVDataStore<KEY_T, Value_T> &data, size_t sampleSize)
{
    if (data.empty() || sampleSize == 0)
        return {};

    nr::VectorData<Value_T> out;
    //out.reserve(sampleSize);

    // Просто перебираем все группы и добавляем элементы по порядку
    for (const auto& [label, values] : data)
    {
        for (const auto& v : values)
        {
            if (out.size() >= sampleSize)
                return out;  // досчитали до sampleSize
            out.push_back(v);
        }
    }

    return out; // если sampleSize больше, чем элементов — возвращаем всё
}

template <typename KEY_T, typename Value_T>
inline nr::VectorData<Value_T> nr::NonProbabilitySampling::convenienceSample(const nr::CSVDataStore<KEY_T, Value_T> &data, size_t sampleSize)
{
    if (data.empty() || sampleSize == 0)
        return {};

    nr::VectorData<Value_T> out;
    //out.reserve(sampleSize);

    // We take elements by availability (for example, the first elements in the group order)
    for (const auto& [label, values] : data)
    {
        for (const auto& v : values)
        {
            if (out.size() >= sampleSize)
                return out;
            out.push_back(v);
        }
    }

    return out; // If sampleSize is greater than the number of elements, we return everything.
}


#endif //NON_PROBABILITY_SAMPLIG_H