#ifndef NUMERA_STATS_BASICSTATS_H
#define NUMERA_STATS_BASICSTATS_H
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include<map>
#include<vector>

namespace nr
{
    template <typename T>
    typename T::value_type min(T& data)
    {
        auto it = std::min_element(data.begin(), data.end());
        return (*it);
    }
    
    template<typename key_type, typename data_type>
    data_type min(const std::map<key_type, std::vector<data_type>>& data)
    {
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
        auto it = std::max_element(data.begin(), data.end());
        return *it;
    }

    template<typename key_type, typename data_type>
    data_type max(const std::map<key_type, std::vector<data_type>>& data)
    {
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

    template <typename T>
    typename T::value_type mean(T& data)
    {
        // Calculates the arithmetic mean
        if (data.empty()) return 0.0;
        typename T::value_type sum = std::accumulate(data.cbegin(), data.cend(), 0.0);
        return sum/data.size();
    }

    template <typename Container>
    auto median(const Container& data) -> typename std::decay_t<Container>::value_type
    {
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
    /*
    template <typename Container>
    double stddev() 
    {
        // standard deviation
    }

    template <typename Container>
    double variance()
    {
        // variance
    }
        */
}
#endif // NUMERA_STATS_BASICSTATS_H