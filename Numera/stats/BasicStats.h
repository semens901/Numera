#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace nr
{
    template <typename Container>
    typename Container::value_type min(Container& data)
    {
        auto it = std::min_element(data.begin(), data.end());
        return (*it);
    }
    
    template <typename Container>
    typename Container::value_type max(Container& data)
    {
        auto it = std::max_element(data.begin(), data.end());
        return *it;
    }

    template <typename Container>
    typename Container::value_type mean(Container& data)
    {
        if (data.empty()) return 0.0;
        typename Container::value_type sum = std::accumulate(data.begin(), data.end(), 0.0);
        return sum/data.size();
    }

    template <typename Container>
    typename Container::value_type median(Container& data)
    {
        if (data.empty()) return 0.0;
        Container numbersCopy(data);
        std::sort(numbersCopy.begin(), numbersCopy.end());
        size_t size = numbersCopy.size();
        if(size % 2 == 1)
        {
            return numbersCopy[size / 2];
        }
        else
        {
            return (numbersCopy[size / 2 - 1] +
                numbersCopy[size / 2]) / 2.0;
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