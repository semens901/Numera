#ifndef NUMERA_STATS_BASICSTATS_H
#define NUMERA_STATS_BASICSTATS_H
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include<map>
#include<vector>
#include <cmath>
#include <type_traits>

namespace nr
{
    template <typename T>
    typename T::value_type min(T& data)
    {
        // Finds the minimum element
     
        if (data.empty()) 
        {
            throw std::invalid_argument("min: empty container");
        }

        auto it = std::min_element(data.begin(), data.end());
        return (*it);
    }
    
    template<typename key_type, typename data_type>
    data_type min(const std::map<key_type, std::vector<data_type>>& data)
    {
        // Finds the minimum element among all values ​​(not counting keys)
        if (data.empty()) 
        {
            throw std::invalid_argument("min: empty container");
        }
        std::vector<data_type> out;
        for(const auto& [key, vec] : data)
        {
            if (vec.empty())
                continue;

            auto it = std::min_element(vec.begin(), vec.end());
            data_type local = *it;
            out.push_back(local);
        }
        auto it = std::min_element(out.begin(), out.end());
        return (*it);
    }

    template <typename T>
    typename T::value_type max(T& data)
    {
        // Finds the maximum element

        if (data.empty()) 
        {
            throw std::invalid_argument("max: empty container");
        }
        auto it = std::max_element(data.begin(), data.end());
        return *it;
    }

    template<typename key_type, typename data_type>
    data_type max(const std::map<key_type, std::vector<data_type>>& data)
    {
        // Finds the maximum element among all values ​​(not counting keys)

        if (data.empty()) 
        {
            throw std::invalid_argument("max: empty container");
        }

        std::vector<data_type> out;
        for(const auto& [key, vec] : data)
        {
            if (vec.empty())
                continue;

            auto it = std::max_element(vec.begin(), vec.end());
            data_type local = *it;
            out.push_back(local);
        }
        auto it = std::max_element(out.begin(), out.end());
        return (*it);
    }

    template <typename Container>
    auto arithmetic_mean(const Container& data) -> typename std::decay_t<Container>::value_type
    {
        // Calculates the arithmetic mean

        if (data.empty()) 
        {
            throw std::invalid_argument("arithmetic_mean: empty container");
        }

        using T = typename std::decay_t<Container>::value_type;
        if (data.empty()) return 0.0;
        T sum = std::accumulate(data.cbegin(), data.cend(), 0.0);
        return sum/data.size();
    }

    template <typename Container>
    auto median(const Container& data) -> typename std::decay_t<Container>::value_type
    {
        // Finds the median
        using mut_container = std::decay_t<Container>;
        using value_type = typename mut_container::value_type;

        if (std::begin(data) == std::end(data)) return value_type{};

        // Make a mutable copy (decayed type) even if `Container` is const-qualified
        mut_container numbersCopy(std::begin(data), std::end(data));
        std::sort(numbersCopy.begin(), numbersCopy.end());

        size_t n = numbersCopy.size();
        if (n % 2 == 1) {
            return numbersCopy[n / 2];
        } else {
            // compute average of two middle elements, cast to value_type
            return (numbersCopy[n / 2 - 1] + numbersCopy[n / 2]) / static_cast<value_type>(2);
        }
    }
    
    template <typename T, typename W>
    auto weighted_mean(
        const std::vector<T>& values,
        const std::vector<W>& weights
    ) -> std::decay_t<decltype(
            std::declval<T>() * std::declval<W>())>
    {
        /*
            The function finds a weighted average value, the first parameter is the population, the second is the "weight" of each population
        */

        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );

        if (values.size() != weights.size()) {
            throw std::invalid_argument("Values and weights must have the same size");
        }

        double sum = 0.0;
        double weight_sum = 0.0;

        for (std::size_t i = 0; i < values.size(); ++i) {
            sum += values[i] * weights[i];
            weight_sum += weights[i];
        }

        if (weight_sum == 0.0) {
            throw std::runtime_error("Sum of weights is zero");
        }

        return sum / weight_sum;
    }

    template <typename Container>
    auto geometric_mean(const Container& data) -> typename std::decay_t<Container>::value_type
    {
        // finds the geometric mean
        using T = typename std::decay_t<Container>::value_type;
        static_assert(
            std::is_arithmetic_v<typename Container::value_type>,
            "geometric_mean requires arithmetic type"
        );

        if (data.empty()) {
            throw std::invalid_argument("Data vector is empty");
        }

        double log_sum = std::accumulate(
            data.begin(), data.end(),
            0.0,
            [](double acc, T value) {
                if (value <= static_cast<T>(0)) {
                    throw std::domain_error(
                        "Geometric mean requires positive values"
                    );
                }
                return acc + std::log(static_cast<double>(value));
            }
        );

        return std::exp(log_sum / data.size());
    }

    template <typename Container>
    auto harmonic_mean(const Container& data) -> typename std::decay_t<Container>::value_type
    {
        // finds the harmonic mean
        using T = typename std::decay_t<Container>::value_type;
        static_assert(
            std::is_arithmetic_v<T>,
            "harmonic_mean requires arithmetic type"
        );

        if (data.empty()) {
            throw std::invalid_argument("Data vector is empty");
        }

        double reciprocal_sum = std::accumulate(
            data.begin(), data.end(),
            0.0,
            [](double acc, T value) {
                if (value <= static_cast<T>(0)) {
                    throw std::domain_error(
                        "Harmonic mean requires positive values"
                    );
                }
                return acc + 1.0 / static_cast<double>(value);
            }
        );

        return static_cast<double>(data.size()) / reciprocal_sum;
    }

    template <typename Container>
    auto lower_quartile(const Container& data)
        -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        // Finds the lower quartile
        using mut_container = std::decay_t<Container>;
        using value_type = typename mut_container::value_type;

        if (data.empty()) {
            throw std::invalid_argument("lower_quartile: empty data");
        }

        mut_container dataCopy(data.begin(), data.end());
        std::sort(dataCopy.begin(), dataCopy.end());

        const std::size_t size_ = dataCopy.size();
        const std::size_t mid = size_ / 2;

        if (mid == 0) {
            throw std::logic_error("lower_quartile: not enough data");
        }

        mut_container dataLower(dataCopy.begin(), dataCopy.begin() + mid);

        return median(dataLower);
    }

    template <typename Container>
    auto upper_quartile(const Container& data)
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        // Finds the upper quartile
        using mut_container = std::decay_t<Container>;

        if (data.empty()) {
            throw std::invalid_argument("upper_quartile: empty data");
        }

        mut_container dataCopy(data.begin(), data.end());
        std::sort(dataCopy.begin(), dataCopy.end());

        const std::size_t n = dataCopy.size();
        const std::size_t mid = n / 2;

        if (mid == 0) {
            throw std::logic_error("upper_quartile: not enough data");
        }

        // для нечётного n пропускаем медиану
        const std::size_t start =
            (n % 2 == 0) ? mid : mid + 1;

        mut_container dataUpper(
            dataCopy.begin() + start,
            dataCopy.end()
        );

        return median(dataUpper);
    }

}
#endif // NUMERA_STATS_BASICSTATS_H