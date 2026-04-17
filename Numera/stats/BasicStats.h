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

namespace nr
{
    // Forward declaration of CSVTable to allow providing overloads
    // without including CSVTable.h (avoids circular include).

    template<typename Iterator>
    auto min(Iterator begin, Iterator end) 
    -> typename std::iterator_traits<Iterator>::value_type
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
    -> typename std::decay_t<Container>::value_type
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
    auto max(Iterator begin, Iterator end) -> typename std::iterator_traits<Iterator>::value_type
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
    -> typename std::decay_t<Container>::value_type
    {
        // Returns the maximum value in the range (data.begin, data.end)
        // Throws if the range is empty.

        if (data.empty()) 
        {
            throw std::invalid_argument("max: empty container");
        }
        return *std::max_element(data.begin(), data.end());
    }

    template<typename Iterator>
    auto arithmetic_mean(Iterator begin, Iterator end, typename std::iterator_traits<Iterator>::value_type init) 
    -> typename std::iterator_traits<Iterator>::value_type
    {
        // Calculates the arithmetic arithmetic_mean
        // Throws if the range is empty.
        if (begin == end) 
        {
            throw std::invalid_argument("arithmetic_mean: empty container");
        }

        using T = typename std::iterator_traits<Iterator>::value_type;

        T sum = std::accumulate(begin, end, init);
        return sum/std::distance(begin, end);
    }

    template <typename Container>
    auto arithmetic_mean(const Container& data) 
    -> typename std::decay_t<Container>::value_type
    {
        // Calculates the arithmetic arithmetic_mean
        // Throws if the range is empty.
        if (data.empty()) 
        {
            throw std::invalid_argument("arithmetic_mean: empty container");
        }

        using T = typename std::decay_t<Container>::value_type;

        T sum = std::accumulate(data.cbegin(), data.cend(), 0.0);
        return sum/data.size();
    }

    template<typename Iterator>
    auto median(Iterator begin, Iterator end) -> typename std::iterator_traits<Iterator>::value_type
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
    auto median(const Container& data) -> typename std::decay_t<Container>::value_type
    {
        // Finds the median
        // Throws if the range is empty.
        using mut_container = std::decay_t<Container>;
        using value_type = typename mut_container::value_type;

        if (std::begin(data) == std::end(data)) throw std::invalid_argument("median: empty container");

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
        using returnType = std::decay_t<decltype(std::declval<T>() * std::declval<W>())>;
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

        returnType  sum = 0.0;
        returnType  weight_sum = 0.0;

        for (std::size_t i = 0; i < values.size(); ++i) {
            sum += values[i] * weights[i];
            weight_sum += weights[i];
        }

        if (weight_sum == 0.0) {
            throw std::runtime_error("Sum of weights is zero");
        }

        return sum / weight_sum;
    }

    template <typename Container, typename Weight>
    auto weighted_mean(
        const Container& values,
        const Weight& weights
    ) -> std::decay_t<decltype(
            std::declval<typename Container::value_type>() * std::declval<typename Weight::value_type>())>
    {
        /*
            The function finds a weighted average value, the first parameter is the population, the second is the "weight" of each population
        */
        using T = typename Container::value_type;
        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );

        if (values.size() != weights.size()) {
            throw std::invalid_argument("Values and weights must have the same size");
        }

        T sum = 0.0;
        T weight_sum = 0.0;

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
    auto geometric_mean(const Container& data) 
    -> typename std::decay_t<Container>::value_type
    {
        // finds the geometric arithmetic_mean
        using T = typename std::decay_t<Container>::value_type;
        static_assert(
            std::is_arithmetic_v<typename Container::value_type>,
            "geometric_mean requires arithmetic type"
        );

        if (data.empty()) {
            throw std::invalid_argument("Data vector is empty");
        }

        T log_sum = std::accumulate(
            data.begin(), data.end(),
            0.0,
            [](T acc, T value) {
                if (value <= static_cast<T>(0)) {
                    throw std::domain_error(
                        "Geometric arithmetic_mean requires positive values"
                    );
                }
                return acc + std::log(static_cast<T>(value));
            }
        );

        return std::exp(log_sum / data.size());
    }

    template<typename Iterator>
    auto geometric_mean(Iterator begin, Iterator end) 
    -> typename std::iterator_traits<Iterator>::value_type
    {
        // finds the geometric arithmetic_mean
        using T = typename std::iterator_traits<Iterator>::value_type;
        using returnType = std::decay_t<decltype(std::declval<T>() * std::declval<T>())>;
        static_assert(
            std::is_arithmetic_v<T>,
            "geometric_mean requires arithmetic type"
        );

        if (begin == end) {
            throw std::invalid_argument("Data vector is empty");
        }

        returnType log_sum = std::accumulate(
            begin, end,
            0.0,
            [](double acc, T value) {
                if (value <= static_cast<T>(0)) {
                    throw std::domain_error(
                        "Geometric arithmetic_mean requires positive values"
                    );
                }
                return acc + std::log(static_cast<T>(value));
            }
        );

        return std::exp(log_sum / std::distance(begin, end));
    }

    template <typename Container>
    auto harmonic_mean(const Container& data) 
    -> typename std::decay_t<Container>::value_type
    {
        // finds the harmonic arithmetic_mean
        using T = typename std::decay_t<Container>::value_type;
        using returnType = std::decay_t<decltype(std::declval<T>() * std::declval<T>())>;
        static_assert(
            std::is_arithmetic_v<T>,
            "harmonic_mean requires arithmetic type"
        );

        if (data.empty()) {
            throw std::invalid_argument("Data vector is empty");
        }

        returnType reciprocal_sum = std::accumulate(
            data.begin(), data.end(),
            0.0,
            [](returnType acc, T value) {
                if (value <= static_cast<T>(0)) {
                    throw std::domain_error(
                        "Harmonic arithmetic_mean requires positive values"
                    );
                }
                return acc + 1.0 / static_cast<T>(value);
            }
        );

        return static_cast<T>(data.size()) / reciprocal_sum;
    }

    template<typename Iterator>
    auto harmonic_mean(Iterator begin, Iterator end) 
    -> typename std::iterator_traits<Iterator>::value_type
    {
        // finds the harmonic arithmetic_mean
        using T = typename std::iterator_traits<Iterator>::value_type;
        static_assert(
            std::is_arithmetic_v<T>,
            "harmonic_mean requires arithmetic type"
        );

        if (begin == end) {
            throw std::invalid_argument("Data vector is empty");
        }

        T reciprocal_sum = std::accumulate(
            begin, end,
            0.0,
            [](T acc, T value) {
                if (value <= static_cast<T>(0)) {
                    throw std::domain_error(
                        "Harmonic arithmetic_mean requires positive values"
                    );
                }
                return acc + 1.0 / static_cast<T>(value);
            }
        );

        return static_cast<T>(std::distance(begin, end) / reciprocal_sum);
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

    template<typename Iterator>
    auto lower_quartile(Iterator begin, Iterator end) 
    -> typename std::iterator_traits<Iterator>::value_type
    {
        // Finds the lower quartile
        using mut_container = std::vector<typename std::iterator_traits<Iterator>::value_type>;
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
    -> typename std::iterator_traits<Iterator>::value_type
    {
        // Finds the upper quartile
        using mut_container = std::vector<typename std::iterator_traits<Iterator>::value_type>;

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
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        /**
     * Calculates the p-th percentile using linear interpolation (R7/Excel style).
     * * Nuances:
     * - Complexity: O(N log N) due to full internal copy & sort.
     * - Interpolation: Uses (p/100)*(n-1) to find the fractional index.
     * - Safety: Throws if data is empty or p is out of [0, 100] range.
     * - Precision: Returns double to handle fractional results between elements.
     */
        using value_type = typename std::decay_t<Container>::value_type;
        using returnType = std::common_type_t<value_type, double>;

        if (data.empty())
            throw std::invalid_argument("percentile: empty data");

        if (p < 0.0 || p > 100.0)
            throw std::out_of_range("percentile: p must be in [0, 100]");

        std::vector<value_type> sorted(data.begin(), data.end());
        std::sort(sorted.begin(), sorted.end());

        const std::size_t n = sorted.size();
        const returnType pos = (p / 100.0) * (n - 1);

        const std::size_t idx = static_cast<std::size_t>(std::floor(pos));
        const returnType frac = pos - idx;

        if (idx + 1 < n)
            return sorted[idx] * (1.0 - frac) + sorted[idx + 1] * frac;
        else
            return sorted[idx];
    }

    template<typename Iterator>
    auto percentile(const Iterator& begin, const Iterator& end, double p)
    -> std::common_type_t<typename std::iterator_traits<Iterator>::value_type, double>
    {
        /**
         * Calculates the p-th percentile using linear interpolation (R7/Excel style).
         * * Nuances:
         * - Complexity: O(N log N) due to full internal copy & sort.
         * - Interpolation: Uses (p/100)*(n-1) to find the fractional index.
         * - Safety: Throws if data is empty or p is out of [0, 100] range.
         * - Precision: Returns double to handle fractional results between elements.
         */
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using returnType = std::common_type_t<value_type, double>;

         if (begin == end)
             throw std::invalid_argument("percentile: empty data");

         if (p < 0.0 || p > 100.0)
             throw std::out_of_range("percentile: p must be in [0, 100]");

        if (begin == end)
            throw std::invalid_argument("percentile: empty data");

        if (p < 0.0 || p > 100.0)
            throw std::out_of_range("percentile: p must be in [0, 100]");

        std::vector<value_type> sorted(begin, end);
        std::sort(sorted.begin(), sorted.end());

        const std::size_t n = sorted.size();
        const returnType pos = (p / 100.0) * (n - 1);

        const std::size_t idx = static_cast<std::size_t>(std::floor(pos));
        const returnType frac = pos - idx;

        if (idx + 1 < n)
            return sorted[idx] * (1.0 - frac) + sorted[idx + 1] * frac;
        else
            return sorted[idx];
    }

    template <typename Container>
    auto mode(const Container& data)
    -> std::optional<typename std::decay_t<Container>::value_type>
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
    auto mode(const Iterator& begin, const Iterator& end)
    -> std::optional<typename std::iterator_traits<Iterator>::value_type>
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

        for(const auto& v = begin; v != end; ++v)
            ++freq[*v];

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

    template <typename Container>
    auto modes(const Container& data)
    -> std::vector<typename std::decay_t<Container>::value_type>
    {
        /**
         * Finds all modes in a container (supports multi-modal distributions).
         * - Logic: Returns a vector of values with the highest frequency.
         * - Edge Cases: Returns an empty vector if data is empty or all elements are unique (max_count=1).
         * - Complexity: O(N) average time (two passes over the frequency map).
         * - Requirements: value_type must be hashable.
         */
        using T = typename std::decay_t<Container>::value_type;

        if (data.empty())
            return {};

        std::unordered_map<T, std::size_t> freq;

        for (const auto& v : data)
            ++freq[v];

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

        return result;
    }

    template <typename Iterator>
    auto modes(const Iterator& begin, const Iterator& end)
    -> std::vector<typename std::iterator_traits<Iterator>::value_type>
    {
        /**
         * Finds all modes in a container (supports multi-modal distributions).
         * - Logic: Returns a vector of values with the highest frequency.
         * - Edge Cases: Returns an empty vector if data is empty or all elements are unique (max_count=1).
         * - Complexity: O(N) average time (two passes over the frequency map).
         * - Requirements: value_type must be hashable.
         */
        using T = typename std::iterator_traits<Iterator>::value_type;

        if (begin == end)
            return {};

        std::unordered_map<T, std::size_t> freq;

        for(const auto& v = begin; v != end; ++v)
            ++freq[*v];

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

        return result;
    }

    template <typename Container>
    auto Scope(const Container& data)
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        return max(data) - min(data);
    }

    template <typename Iterator>
    auto Scope(const Iterator& begin, const Iterator& end)
    -> std::common_type_t<typename std::iterator_traits<Iterator>::value_type, double>
    {
        return max(begin, end) - min(begin, end);
    }

    template <typename Container>
    auto interquartile_range(const Container& data)
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        return upper_quartile(data) - lower_quartile(data);
    }

    template <typename Iterator>
    auto interquartile_range(const Iterator& begin, const Iterator& end)
    -> std::common_type_t<typename std::iterator_traits<Iterator>::value_type, double>
    {
        return upper_quartile(begin, end) - lower_quartile(begin, end);
    }

    template <typename Container>
    auto mean_absolute_deviation(const Container& data) 
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        using T = typename std::decay_t<Container>::value_type;
        using returnType = std::common_type_t<T, double>;

        if (data.empty()) {
            throw std::invalid_argument("MAD: empty data");
        }

        const returnType n = static_cast<returnType>(data.size());

        returnType sum = arithmetic_mean(data.begin(), data.end(), 0.0);

        returnType total_deviation = 0.0;
        for (const auto& value : data) {
            total_deviation += std::abs(static_cast<double>(value) - sum);
        }

        return total_deviation / n;
    }

    template <typename Iterator>
    auto mean_absolute_deviation(const Iterator& begin, const Iterator& end) 
    -> std::common_type_t<typename std::iterator_traits<Iterator>::value_type, double>
    {
        using T = typename std::iterator_traits<Iterator>::value_type;
        using returnType = std::common_type_t<T, double>;
        if (begin==end) {
            throw std::invalid_argument("MAD: empty data");
        }

        const returnType n = static_cast<returnType>(std::distance(begin, end));

        returnType sum = arithmetic_mean(begin, end, 0.0);

        returnType total_deviation = 0.0;
        for(auto it = begin; it != end; ++it) {
            total_deviation += std::abs(static_cast<returnType>(*it) - sum);
        }

        return total_deviation / n;
    }

    template <typename Container>
    auto dispersion(const Container& data) 
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        using T = typename std::decay_t<Container>::value_type;
        using returnType = std::common_type_t<T, double>;

        if (data.empty()) {
            throw std::invalid_argument("MAD: empty data");
        }

        const returnType n = static_cast<returnType>(data.size());

        returnType sum = arithmetic_mean(data.begin(), data.end(), 0.0);

        returnType total_deviation = 0.0;
        for (const auto& value : data) {
            total_deviation += std::pow((static_cast<double>(value) - sum), 2);
        }

        return total_deviation / n;
    }

    template <typename Iterator>
    auto dispersion(const Iterator& begin, const Iterator& end) 
    -> std::common_type_t<typename std::iterator_traits<Iterator>::value_type, double>
    {
        using T = typename std::iterator_traits<Iterator>::value_type;
        using returnType = std::common_type_t<T, double>;
        if (begin==end) {
            throw std::invalid_argument("MAD: empty data");
        }

        const returnType n = static_cast<returnType>(std::distance(begin, end));

        returnType sum = arithmetic_mean(begin, end, 0.0);

        returnType total_deviation = 0.0;
        for(auto it = begin; it != end; ++it) {
            total_deviation += std::pow((static_cast<returnType>(*it) - sum), 2);
        }

        return total_deviation / n;
    }

    template <typename Container>
    auto standard_deviation(const Container& data) 
    -> std::common_type_t<typename std::decay_t<Container>::value_type, double>
    {
        using T = typename std::decay_t<Container>::value_type;
        using returnType = std::common_type_t<T, double>;

        if (data.empty()) {
            throw std::invalid_argument("MAD: empty data");
        }

        const returnType n = static_cast<returnType>(data.size());

        returnType sum = arithmetic_mean(data.begin(), data.end(), 0.0);

        returnType total_deviation = 0.0;
        for (const auto& value : data) {
            total_deviation += std::pow((static_cast<double>(value) - sum), 2);
        }

        return std::sqrt(total_deviation / n);
    }
    
    template <typename Iterator>
    auto standard_deviation(const Iterator& begin, const Iterator& end) 
    -> std::common_type_t<typename std::iterator_traits<Iterator>::value_type, double>
    {
        using T = typename std::iterator_traits<Iterator>::value_type;
        using returnType = std::common_type_t<T, double>;
        if (begin==end) {
            throw std::invalid_argument("MAD: empty data");
        }

        const returnType n = static_cast<returnType>(std::distance(begin, end));

        returnType sum = arithmetic_mean(begin, end, 0.0);

        returnType total_deviation = 0.0;
        for(auto it = begin; it != end; ++it) {
            total_deviation += std::pow((static_cast<returnType>(*it) - sum), 2);
        }

        return std::sqrt(total_deviation / n);
    }

}
#endif // NUMERA_STATS_BASICSTATS_H