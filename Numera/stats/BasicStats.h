#ifndef NUMERA_STATS_BASICSTATS_H
#define NUMERA_STATS_BASICSTATS_H
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <map>
#include <vector>
#include <cmath>
#include <type_traits>
#include <optional>
#include <unordered_map>

#include "utils/type_traits.h"

namespace nr
{
    // Forward declaration of CSVTable to allow providing overloads
    // without including CSVTable.h (avoids circular include).

    template<typename Iterator>
    auto min(Iterator begin, Iterator end) 
    -> iterator_value_type_t<Iterator>
    {
        // Returns the minimum value in the range (begin, end). 
        // Throws if the range is empty.
        if(begin == end)
            throw std::invalid_argument("min: empty container");
        auto it = std::min_element(begin, end);
        return (*it);
    }

    template <typename Container>
    auto min(const Container& data) 
    -> value_type_t<Container>
    {
        // Returns the minimum value in the range [data.begin(), data.end()].
        // Throws std::invalid_argument if the container is empty.
        //
        // Note: This function is intended to work with sequential containers
        // (e.g., std::vector, std::list, std::deque) that provide iterators.
        // It is not suitable for associative containers where ordering semantics differ.

        if (data.empty()) 
        {
            throw std::invalid_argument("min: empty container");
        }

        return *std::min_element(data.begin(), data.end());
    }

    template<typename Iterator>
    auto max(Iterator begin, Iterator end) 
    -> iterator_value_type_t<Iterator>
    {
        // Returns the maximum value in the range (begin, end)
        // Throws if the range is empty.
        if(begin == end)
            throw std::invalid_argument("max: empty container");
        auto it = std::max_element(begin, end);
        return (*it);
    }

    template <typename Container>
    auto max(const Container& data) 
    -> value_type_t<Container>
    {
        // Returns the maximum value in the range (data.begin, data.end)
        // Throws if the range is empty.

        if (data.empty()) 
        {
            throw std::invalid_argument("max: empty container");
        }
        return *std::max_element(data.begin(), data.end());
    }

    template <typename Container>
    auto arithmetic_mean(const Container& data) 
    -> conditional_type_f<Container, double>
    {
        // Calculates the arithmetic arithmetic_mean
        // Throws if the range is empty.
        if (data.empty()) 
        {
            throw std::invalid_argument("arithmetic_mean: empty container");
        }

        using T = typename std::decay_t<Container>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        CalcType sum = std::accumulate(data.cbegin(), data.cend(), CalcType(0));
        return sum/data.size();
    }

    template<typename Iterator>
    auto arithmetic_mean(Iterator begin, Iterator end) 
    -> iterator_conditional_type_f<Iterator, double>
    {
        // Calculates the arithmetic arithmetic_mean
        // Throws if the range is empty.
        if (begin == end) 
        {
            throw std::invalid_argument("arithmetic_mean: empty container");
        }

        using T = typename std::iterator_traits<Iterator>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        CalcType sum = std::accumulate(begin, end, CalcType(0));
        return sum/std::distance(begin, end);
    }

    template<typename Iterator>
    auto median(Iterator begin, Iterator end) 
    -> iterator_value_type_t<Iterator>
    {
        // Finds the median
        // Throws if the range is empty.
        using mut_container = std::vector<typename std::iterator_traits<Iterator>::value_type>;
        using value_type = typename mut_container::value_type;

        if (begin == end) throw std::invalid_argument("median: empty container");;

        // Make a mutable copy (decayed type) even if `Container` is const-qualified
        mut_container numbersCopy(begin, end);
        std::sort(numbersCopy.begin(), numbersCopy.end());

        size_t n = numbersCopy.size();
        if (n % 2 == 1) {
            return numbersCopy[n / 2];
        } else {
            // compute average of two middle elements, cast to value_type
            return (numbersCopy[n / 2 - 1] + numbersCopy[n / 2]) / static_cast<value_type>(2);
        }
    }

    template <typename Container>
    auto median(const Container& data) 
    -> value_type_t<Container>
    {
        // Finds the median
        // Throws if the range is empty.
        using mut_container = std::decay_t<Container>;
        using T = typename mut_container::value_type;

        if (std::begin(data) == std::end(data)) throw std::invalid_argument("median: empty container");

        // Make a mutable copy (decayed type) even if `Container` is const-qualified
        mut_container numbersCopy(std::begin(data), std::end(data));
        std::sort(numbersCopy.begin(), numbersCopy.end());

        size_t n = numbersCopy.size();
        if (n % 2 == 1) {
            return numbersCopy[n / 2];
        } else {
            // compute average of two middle elements, cast to value_type
            return (numbersCopy[n / 2 - 1] + numbersCopy[n / 2]) / static_cast<T>(2);
        }
    }

    template <typename Container, typename Weight>
    auto weighted_mean(
        const Container& values,
        const Weight& weights
    )
    -> conditional_type_f<Container, double>
    {
        /*
            The function finds a weighted average value, the first parameter is the population, the second is the "weight" of each population
        */
        using T = typename Container::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );

        if (values.size() != weights.size()) {
            throw std::invalid_argument("Values and weights must have the same size");
        }

        CalcType sum = 0.0;
        CalcType weight_sum = 0.0;

        for (std::size_t i = 0; i < values.size(); ++i) {
            sum += values[i] * weights[i];
            weight_sum += weights[i];
        }

        if (weight_sum == 0.0) {
            throw std::runtime_error("Sum of weights is zero");
        }

        return sum / weight_sum;
    }

    template <typename IteratorData, typename IteratorWeight>
    auto weighted_mean(
        IteratorData beginData,
        IteratorData endData,
        IteratorWeight beginWeight,
        IteratorWeight endWeight
    ) 
    -> iterator_conditional_type_f<IteratorData, double>
    {
        /*
            The function finds a weighted average value, the first parameter is the population (begin, end), the second is the "weight"(begin, end) of each population
        */
        
        using T = typename std::iterator_traits<IteratorData>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );
        
        size_t distance_data = std::distance(beginData, endData);
        size_t distance_Weight = std::distance(beginWeight, endWeight);
        
        if (distance_data != distance_Weight) 
        {
            throw std::invalid_argument("Values and weights must have the same size");
        }

        CalcType sum = 0.0;
        CalcType weight_sum = 0.0;
        
        for (std::pair<IteratorData, IteratorWeight> it_pair{beginData, beginWeight}; (it_pair.first != endData) && (it_pair.second != endWeight); ++it_pair.first, ++it_pair.second)
        {
            sum += *it_pair.first * *it_pair.second;
            weight_sum += *it_pair.second;
        }

        if (weight_sum == 0.0) {
            throw std::runtime_error("Sum of weights is zero");
        }

        return sum / weight_sum;
    }

    template <typename IteratorData, typename IteratorWeight>
    auto weighted_mean(
        IteratorData beginData,
        IteratorData endData,
        IteratorWeight beginWeight
    ) 
    -> iterator_conditional_type_f<IteratorData, double>
    {
        /*
            Computes the weighted mean for the data range [beginData, endData)
            using weights provided starting from `beginWeight`. The function
            advances the weight iterator in lockstep with the data iterator.

            WARNING: This overload is unsafe because it does NOT verify that
            the weight iterator range is long enough or matches the data
            range. Passing a shorter or mismatched weight sequence leads to
            undefined behavior. Callers must ensure the weight range corresponds
            to the data range before invoking this function.
        */

        using T = typename std::iterator_traits<IteratorData>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );
        
        if (std::distance(beginData, endData) == 0) 
        {
            throw std::invalid_argument("Values ​​cannot be empty");
        }

        CalcType sum = 0.0;
        CalcType weight_sum = 0.0;
        
        for (std::pair<IteratorData, IteratorWeight> it_pair{beginData, beginWeight}; it_pair.first != endData; ++it_pair.first, ++it_pair.second)
        {
            sum += *it_pair.first * *it_pair.second;
            weight_sum += *it_pair.second;
        }

        if (weight_sum == 0.0) {
            throw std::runtime_error("Sum of weights is zero");
        }

        return sum / weight_sum;
    }

    template <typename Container>
    auto geometric_mean(const Container& data) 
    -> conditional_type_f<Container, double>
    {
        // finds the geometric arithmetic_mean
        using T = typename std::decay_t<Container>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
        
        static_assert(
            std::is_arithmetic_v<typename Container::value_type>,
            "geometric_mean requires arithmetic type"
        );

        if (data.empty()) {
            throw std::invalid_argument("Data is empty");
        }

        CalcType log_sum = std::accumulate(
            data.begin(), data.end(),
            0.0,
            [](CalcType acc, CalcType value) {
                if (value <= static_cast<CalcType>(0)) {
                    throw std::domain_error(
                        "Geometric arithmetic_mean requires positive values"
                    );
                }
                return acc + std::log(static_cast<CalcType>(value));
            }
        );

        return std::exp(log_sum / data.size());
    }

    template<typename Iterator>
    auto geometric_mean(Iterator begin, Iterator end) 
    -> iterator_conditional_type_f<Iterator, double>
    {
        // finds the geometric arithmetic_mean
        using T = typename std::iterator_traits<Iterator>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );

        if (begin == end) {
            throw std::invalid_argument("Data begin equals end is empty");
        }

        CalcType log_sum = std::accumulate(
            begin, end,
            0.0,
            [](CalcType acc, CalcType value) {
                if (value <= static_cast<CalcType>(0)) {
                    throw std::domain_error(
                        "Geometric arithmetic_mean requires positive values"
                    );
                }
                return acc + std::log(static_cast<CalcType>(value));
            }
        );

        return std::exp(log_sum / std::distance(begin, end));
    }

    template <typename Container>
    auto harmonic_mean(const Container& data) 
    -> conditional_type_f<Container, double>
    {
        // finds the harmonic arithmetic_mean
        using T = typename std::decay_t<Container>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        static_assert(
            std::is_arithmetic_v<T>,
            "harmonic_mean requires arithmetic type"
        );

        if (data.empty()) {
            throw std::invalid_argument("Data is empty");
        }

        CalcType reciprocal_sum = std::accumulate(
            data.begin(), data.end(),
            0.0,
            [](CalcType acc, CalcType value) {
                if (value <= static_cast<CalcType>(0)) {
                    throw std::domain_error(
                        "Harmonic arithmetic_mean requires positive values"
                    );
                }
                return acc + 1.0 / static_cast<CalcType>(value);
            }
        );

        return static_cast<CalcType>(data.size()) / reciprocal_sum;
    }

    template<typename Iterator>
    auto harmonic_mean(Iterator begin, Iterator end) 
    -> iterator_conditional_type_f<Iterator, double>
    {
        // finds the harmonic arithmetic_mean
        using T = typename std::iterator_traits<Iterator>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        static_assert(
            std::is_arithmetic_v<T>,
            "harmonic_mean requires arithmetic type"
        );

        if (begin == end) {
            throw std::invalid_argument("Data begin equals end is empty");
        }

        CalcType reciprocal_sum = std::accumulate(
            begin, end,
            0.0,
            [](CalcType acc, CalcType value) {
                if (value <= static_cast<CalcType>(0)) {
                    throw std::domain_error(
                        "Harmonic arithmetic_mean requires positive values"
                    );
                }
                return acc + 1.0 / static_cast<CalcType>(value);
            }
        );

        return static_cast<CalcType>(std::distance(begin, end)) / reciprocal_sum;
    }

    template <typename Container>
    auto lower_quartile(const Container& data)
    -> value_type_t<Container>
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

    template<typename Iterator>
    auto lower_quartile(Iterator begin, Iterator end) 
    -> iterator_value_type_t<Iterator>
    {
        // Finds the lower quartile
        using mut_container = std::vector<iterator_value_type_t<Iterator>>;
        using value_type = typename mut_container::value_type;

        if (begin == end) {
            throw std::invalid_argument("lower_quartile: empty data");
        }

        mut_container dataCopy(begin, end);
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
    -> value_type_t<Container>
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

        // For odd n we skip the median.
        const std::size_t start =
            (n % 2 == 0) ? mid : mid + 1;

        mut_container dataUpper(
            dataCopy.begin() + start,
            dataCopy.end()
        );

        return median(dataUpper);
    }

    template<typename Iterator>
    auto upper_quartile(Iterator begin, Iterator end) 
    -> iterator_value_type_t<Iterator>
    {
        // Finds the upper quartile
        using mut_container = std::vector<iterator_value_type_t<Iterator>>;

        if (begin == end) {
            throw std::invalid_argument("upper_quartile: empty data");
        }

        mut_container dataCopy(begin, end);
        std::sort(dataCopy.begin(), dataCopy.end());

        const std::size_t n = dataCopy.size();
        const std::size_t mid = n / 2;

        if (mid == 0) {
            throw std::logic_error("upper_quartile: not enough data");
        }

        // For odd n we skip the median.
        const std::size_t start =
            (n % 2 == 0) ? mid : mid + 1;

        mut_container dataUpper(
            dataCopy.begin() + start,
            dataCopy.end()
        );

        return median(dataUpper);
    }

    template <typename Container>
    auto percentile(const Container& data, double p)
    -> value_type_t<Container>
    {
        /**
     * Calculates the p-th percentile using linear interpolation (R7/Excel style).
     * * Nuances:
     * - Complexity: O(N log N) due to full internal copy & sort.
     * - Interpolation: Uses (p/100)*(n-1) to find the fractional index.
     * - Safety: Throws if data is empty or p is out of [0, 100] range.
     * - Precision: Returns double to handle fractional results between elements.
     */
        using T = value_type_t<Container>;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        if (data.empty())
            throw std::invalid_argument("percentile: empty data");

        if (p < 0.0 || p > 100.0)
            throw std::out_of_range("percentile: p must be in [0, 100]");

        std::vector<T> sorted(data.begin(), data.end());
        std::sort(sorted.begin(), sorted.end());

        const std::size_t n = sorted.size();
        const CalcType pos = (p / 100.0) * (n - 1);

        const std::size_t idx = static_cast<std::size_t>(std::floor(pos));
        const CalcType frac = pos - idx;

        if (idx + 1 < n)
            return sorted[idx] * (1.0 - frac) + sorted[idx + 1] * frac;
        else
            return sorted[idx];
    }

    template<typename Iterator>
    auto percentile(const Iterator& begin, const Iterator& end, double p)
    -> iterator_value_type_t<Iterator>
    {
        /**
         * Calculates the p-th percentile using linear interpolation (R7/Excel style).
         * * Nuances:
         * - Complexity: O(N log N) due to full internal copy & sort.
         * - Interpolation: Uses (p/100)*(n-1) to find the fractional index.
         * - Safety: Throws if data is empty or p is out of [0, 100] range.
         * - Precision: Returns double to handle fractional results between elements.
         */
        using T = iterator_value_type_t<Iterator>;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

         if (begin == end)
             throw std::invalid_argument("percentile: empty data");

         if (p < 0.0 || p > 100.0)
             throw std::out_of_range("percentile: p must be in [0, 100]");

        if (begin == end)
            throw std::invalid_argument("percentile: empty data");

        if (p < 0.0 || p > 100.0)
            throw std::out_of_range("percentile: p must be in [0, 100]");

        std::vector<T> sorted(begin, end);
        std::sort(sorted.begin(), sorted.end());

        const std::size_t n = sorted.size();
        const CalcType pos = (p / 100.0) * (n - 1);

        const std::size_t idx = static_cast<std::size_t>(std::floor(pos));
        const CalcType frac = pos - idx;

        if (idx + 1 < n)
            return sorted[idx] * (1.0 - frac) + sorted[idx + 1] * frac;
        else
            return sorted[idx];
    }

    template <typename Container>
    auto mode(const Container& data)
    -> std::optional<value_type_t<Container>>
    {
        /**
         * Finds the unique mode of a container.
         * - Logic: Returns the most frequent element only if it's unique.
         * - Edge Cases: Returns std::nullopt if the data is empty, 
         * multi-modal (multiple values with same max frequency), 
         * or if all elements appear only once.
         * - Requirements: value_type must be hashable for std::unordered_map.
         * - Complexity: O(N) average time.
         */
        using T = typename std::decay_t<Container>::value_type;

        if (data.empty())
            return std::nullopt;

        std::unordered_map<T, std::size_t> freq;

        for (const auto& v : data)
            ++freq[v];

        std::size_t max_count = 0;
        T result{};
        bool unique = true;

        for (const auto& [value, count] : freq)
        {
            if (count > max_count)
            {
                max_count = count;
                result = value;
                unique = true;
            }
            else if (count == max_count)
            {
                unique = false;
            }
        }

        if (!unique || max_count == 1)
            return std::nullopt;

        return result;
    }

    template <typename Iterator>
    auto mode(Iterator begin, Iterator end)
    -> std::optional<iterator_value_type_t<Iterator>>
    {
        /**
         * Finds the unique mode of a container.
         * - Logic: Returns the most frequent element only if it's unique.
         * - Edge Cases: Returns std::nullopt if the data is empty, 
         * multi-modal (multiple values with same max frequency), 
         * or if all elements appear only once.
         * - Requirements: value_type must be hashable for std::unordered_map.
         * - Complexity: O(N) average time.
         */
        using T = typename std::iterator_traits<Iterator>::value_type;

        if (begin == end)
            return std::nullopt;

        std::unordered_map<T, std::size_t> freq;

        for(auto it = begin; it != end; ++it)
            ++freq[*it];

        std::size_t max_count = 0;
        std::size_t mode_count = 0;
        std::optional<T> result;

        for (const auto& [value, count] : freq)
        {
            if (count > max_count)
            {
                max_count = count;
                result = value;
                mode_count = 1;
            }
            else if (count == max_count)
            {
                ++mode_count;
            }
        }

        if (max_count <= 1 || mode_count != 1)
            return std::nullopt;

        return result;
    }

    template <typename Container>
    auto modes(const Container& data)
    -> std::vector<value_type_t<Container>>
    {
        /**
         * Finds all modes in a container (supports multi-modal distributions).
         * - Logic: Returns a vector of values with the highest frequency.
         * - Edge Cases: Returns an empty vector if data is empty or all elements are unique (max_count=1).
         * - Complexity: O(N) average time (two passes over the frequency map).
         * - Requirements: value_type must be hashable.
         */
        using T = value_type_t<Container>;

        if (data.empty())
            return {};

        std::unordered_map<T, std::size_t> freq;

        for (const auto& v : data)
            ++freq[v];

        std::size_t max_count = 0;
        for (const auto& [_, count] : freq)
            max_count = std::max(max_count, count);

        if (max_count <= 1)
            return {};

        std::vector<T> result;
        for (const auto& [value, count] : freq)
        {
            if (count == max_count)
                result.push_back(value);
        }
        
        std::sort(result.begin(), result.end());
        return result;
    }

    template <typename Iterator>
    auto modes(Iterator begin, Iterator end)
    -> std::vector<iterator_value_type_t<Iterator>>
    {
        /**
         * Finds all modes in a container (supports multi-modal distributions).
         * - Logic: Returns a vector of values with the highest frequency.
         * - Edge Cases: Returns an empty vector if data is empty or all elements are unique (max_count=1).
         * - Complexity: O(N) average time (two passes over the frequency map).
         * - Requirements: value_type must be hashable.
         */
        using T = iterator_value_type_t<Iterator>;

        if (begin == end)
            return {};

        std::unordered_map<T, std::size_t> freq;

        for(auto it = begin; it != end; ++it)
            ++freq[*it];

        std::size_t max_count = 0;
        for (const auto& [_, count] : freq)
            max_count = std::max(max_count, count);

        if (max_count <= 1)
            return {}; // моды нет

        std::vector<T> result;
        for (const auto& [value, count] : freq)
        {
            if (count == max_count)
                result.push_back(value);
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    template <typename Container>
    auto Scope(const Container& data)
    -> typename std::conditional_t<
    std::is_floating_point_v<
    typename Container::value_type>,
    typename Container::value_type, double>
    {
        /*
         * Calculates the scope (range) of a container.
         * - Logic: Returns the difference between the maximum and minimum values.
         * - Edge Cases: Returns 0 if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */

        if (data.empty())
            throw std::invalid_argument("Scope: empty data");
        return nr::max(data) - nr::min(data);
    }

    template <typename Iterator>
    auto Scope(Iterator begin, Iterator end)
    -> iterator_conditional_type_f<Iterator, double>
    {
        /*
         * Calculates the scope (range) of a container.
         * - Logic: Returns the difference between the maximum and minimum values.
         * - Edge Cases: Returns 0 if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */
        
        if(begin == end)
            throw std::invalid_argument("Scope: empty data");
        
        return (nr::max(begin, end) - nr::min(begin, end));
    }

    template <typename Container>
    auto interquartile_range(const Container& data)
    -> conditional_type_f<Container, double>
    {
        /*
         * Calculates the interquartile range of a container.
         * - Logic: Returns the difference between the upper and lower quartiles.
         * - Edge Cases: Returns 0 if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */

        if (data.empty())
            throw std::invalid_argument("interquartile_range: empty data");

        return upper_quartile(data) - lower_quartile(data);
    }

    template <typename Iterator>
    auto interquartile_range(Iterator begin, Iterator end)
    -> iterator_conditional_type_f<Iterator, double>
    {
        /*
         * Calculates the interquartile range of a container.
         * - Logic: Returns the difference between the upper and lower quartiles.
         * - Edge Cases: Returns 0 if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */

        if(begin == end)
            throw std::invalid_argument("interquartile_range: empty data");
        
        return upper_quartile(begin, end) - lower_quartile(begin, end);
    }

    template <typename Container>
    auto mean_absolute_deviation(const Container& data) 
    -> conditional_type_f<Container, double>
    {
        /**
         * Calculates the mean absolute deviation of a container.
         * - Logic: Returns the average of the absolute deviations from the mean.
         * - Edge Cases: throw std::invalid_argument if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */

        using T = value_type_t<Container>;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        if (data.empty()) {
            throw std::invalid_argument("MAD: empty data");
        }

        const CalcType n = static_cast<CalcType>(data.size());

        CalcType sum = arithmetic_mean(data.begin(), data.end());

        CalcType total_deviation = 0.0;
        for (const auto& value : data) {
            total_deviation += std::abs(static_cast<CalcType>(value) - sum);
        }

        return total_deviation / n;
    }

    template <typename Iterator>
    auto mean_absolute_deviation(Iterator begin, Iterator end) 
    -> iterator_conditional_type_f<Iterator, double>
    {
        /**
         * Calculates the mean absolute deviation of a container.
         * - Logic: Returns the average of the absolute deviations from the mean.
         * - Edge Cases: throw std::invalid_argument if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */
        using T = iterator_value_type_t<Iterator>;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
        if (begin == end) {
            throw std::invalid_argument("MAD: empty data");
        }

        const CalcType n = static_cast<CalcType>(std::distance(begin, end));

        CalcType sum = arithmetic_mean(begin, end);

        CalcType total_deviation = 0.0;
        for(auto it = begin; it != end; ++it) {
            total_deviation += std::abs(static_cast<CalcType>(*it) - sum);
        }

        return total_deviation / n;
    }

    template <typename Container>
    auto dispersion(const Container& data) 
    -> conditional_type_f<Container, double>
    {
        /**
         * Calculates the dispersion (variance) of a container.
         * - Logic: Returns the average of the squared deviations from the mean.
         * - Edge Cases: throw std::invalid_argument if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */
        using T = typename std::decay_t<Container>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        if (data.empty()) {
            throw std::invalid_argument("Dispersion: empty data");
        }

        const CalcType n = static_cast<CalcType>(data.size());

        CalcType sum = arithmetic_mean(data.begin(), data.end());

        CalcType total_deviation = 0.0;
        for (const auto& value : data) {
            total_deviation += std::pow((static_cast<CalcType>(value) - sum), 2);
        }

        return total_deviation / n;
    }

    template <typename Iterator>
    auto dispersion(Iterator begin, Iterator end) 
    -> iterator_conditional_type_f<Iterator, double>
    {
        /**
         * Calculates the dispersion (variance) of a container.
         * - Logic: Returns the average of the squared deviations from the mean.
         * - Edge Cases: throw std::invalid_argument if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */
        using T = iterator_value_type_t<Iterator>;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
        if (begin==end) {
            throw std::invalid_argument("Dispersion: empty data");
        }

        const CalcType n = static_cast<CalcType>(std::distance(begin, end));

        CalcType sum = arithmetic_mean(begin, end);

        CalcType total_deviation = 0.0;
        for(auto it = begin; it != end; ++it) {
            total_deviation += std::pow((static_cast<CalcType>(*it) - sum), 2);
        }

        return total_deviation / n;
    }

    template <typename Container>
    auto standard_deviation(const Container& data) 
    -> conditional_type_f<Container, double>
    {
        /**
         * Calculates the standard deviation of a container.
         * - Logic: Returns the square root of the dispersion.
         * - Edge Cases: throw std::invalid_argument if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */
        using T = typename std::decay_t<Container>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        if (data.empty()) {
            throw std::invalid_argument("Standard Deviation: empty data");
        }

        const CalcType n = static_cast<CalcType>(data.size());

        CalcType sum = arithmetic_mean(data.begin(), data.end());

        CalcType total_deviation = 0.0;
        for (const auto& value : data) {
            total_deviation += std::pow((static_cast<CalcType>(value) - sum), 2);
        }

        return std::sqrt(total_deviation / n);
    }
    
    template <typename Iterator>
    auto standard_deviation(Iterator begin, Iterator end) 
    -> iterator_conditional_type_f<Iterator, double>
    {
        /**
         * Calculates the standard deviation of a container.
         * - Logic: Returns the square root of the dispersion.
         * - Edge Cases: throw std::invalid_argument if data is empty.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable.
         */
        using T = typename std::iterator_traits<Iterator>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
        if (begin==end) {
            throw std::invalid_argument("Standard Deviation: empty data");
        }

        const CalcType n = static_cast<CalcType>(std::distance(begin, end));

        CalcType sum = arithmetic_mean(begin, end);

        CalcType total_deviation = 0.0;
        for(auto it = begin; it != end; ++it) {
            total_deviation += std::pow((static_cast<CalcType>(*it) - sum), 2);
        }

        return std::sqrt(total_deviation / n);
    }

    template<typename Container>
    auto skewness_pearson_1(const Container& data)
    -> conditional_type_f<Container, double>
    {
        /*
            * Calculates Pearson's first coefficient of skewness for a container.
            * - Logic: Returns (mean - mode) / standard deviation.
            * - Edge Cases: throw std::invalid_argument if data is empty or if standard deviation is zero, or if mode is not unique.
            * - Complexity: O(N) time (one pass over the data).
            * - Requirements: value_type must be comparable and arithmetic.
        */

        using T = typename Container::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
        

        CalcType result = 0.0;

        CalcType mean = arithmetic_mean(data);
        CalcType stddev = standard_deviation(data);
        auto modeOpt = mode(data);
        if (!modeOpt.has_value()) {
            throw std::invalid_argument("Pearson's first coefficient of skewness: mode is not unique or does not exist");
        }
        CalcType modeValue = modeOpt.value();
        if (stddev != 0) {
            result = (mean - modeValue) / stddev;
        }
        else
        {
            throw std::invalid_argument("Pearson's first coefficient of skewness: standard deviation is zero");
        }
        return result;
    }

    template<typename Iterator>
    auto skewness_pearson_1(const Iterator& begin, const Iterator& end)
    -> iterator_conditional_type_f<Iterator, double>
    {
        /*
            * Calculates Pearson's first coefficient of skewness for a container.
            * - Logic: Returns (mean - mode) / standard deviation.
            * - Edge Cases: throw std::invalid_argument if data is empty or if standard deviation is zero, or if mode is not unique.
            * - Complexity: O(N) time (one pass over the data).
            * - Requirements: value_type must be comparable and arithmetic.
        */

        using T = typename std::iterator_traits<Iterator>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        CalcType result = 0.0;

        CalcType mean = arithmetic_mean(begin, end);
        CalcType stddev = standard_deviation(begin, end);
        auto modeOpt = mode(begin, end);
        if (!modeOpt.has_value()) {
            throw std::invalid_argument("Pearson's first coefficient of skewness: mode is not unique or does not exist");
        }
        CalcType modeValue = modeOpt.value();
        if (stddev != 0) {
            result = (mean - modeValue) / stddev;
        }
        else
        {
            throw std::invalid_argument("Pearson's first coefficient of skewness: standard deviation is zero");
        }
        return result;
    }

    

    template <typename Container>
    auto skewness_pearson_2(const Container& data)
    -> conditional_type_f<Container, double>
    {
        /*
            * Calculates Pearson's second coefficient of skewness for a container.
            * - Logic: Returns (mean - median) / standard deviation.
            * - Edge Cases: throw std::invalid_argument if data is empty or if standard deviation is zero.
            * - Complexity: O(N) time (one pass over the data).
            * - Requirements: value_type must be comparable and arithmetic.
        */

        using T = typename std::decay_t<Container>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        CalcType result = 0.0;

        CalcType mean = arithmetic_mean(data);
        CalcType stddev = standard_deviation(data);
        CalcType median = median(data);
        if (stddev != 0) {
            result = ((mean - median)*3) / stddev;
        }
        else
        {
            throw std::invalid_argument("Measure of asymmetry: standard deviation is zero");
        }
        return result;
    }

    template <typename Iterator>
    auto skewness_pearson_2(Iterator begin, Iterator end)
    -> iterator_conditional_type_f<Iterator, double>
    {
        /**
         * Calculates Pearson's second coefficient of skewness for a container.
         * - Logic: Returns (mean - median) / standard deviation.
         * - Edge Cases: throw std::invalid_argument if data is empty or if standard deviation is zero.
         * - Complexity: O(N) time (one pass over the data).
         * - Requirements: value_type must be comparable and arithmetic.
         */
        using T = typename std::iterator_traits<Iterator>::value_type;
        using CalcType = std::conditional_t<std::is_floating_point_v<T>, T, double>;

        CalcType result = 0.0;

        CalcType mean = arithmetic_mean(begin, end);
        CalcType stddev = standard_deviation(begin, end);
        CalcType median = median(begin, end);
        if (stddev != 0) {
            result = ((mean - median)*3) / stddev;
        }
        else
        {
            throw std::invalid_argument("Measure of asymmetry: standard deviation is zero");
        }
        return result;
    }

}
#endif // NUMERA_STATS_BASICSTATS_H