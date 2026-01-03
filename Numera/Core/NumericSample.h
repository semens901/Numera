#ifndef NUMERA_CORE_VECTORDATA_H
#define NUMERA_CORE_VECTORDATA_H
#include "stats/BasicStats.h"
#include "io/IDataLoader.h"

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<cmath>

/**
 * @brief A simple vector-based data container with basic statistical operations.
 *
 * NumericSample is a lightweight wrapper around std::vector that provides
 * convenient access, modification, iteration, and common descriptive
 * statistics such as minimum, maximum, arithmetic_mean, and median.
 *
 * The class is intended to represent a one-dimensional numerical dataset
 * and can be populated either directly or via an external data loader.
 *
 * This container owns its data and performs no I/O by itself.
 *
 * @tparam T Type of stored elements (must support comparison and arithmetic operations)
 */

namespace nr
{   
    template <typename T>
    class NumericSample
    {
    public:
        //Stores data in std::vector
        using value_type = T;
        using container_type = std::vector<T>;
        using size_type = std::size_t;
        using iterator = typename container_type::iterator;
        using const_iterator =  typename container_type::const_iterator;

        NumericSample() = default;
        ~NumericSample() = default;
        NumericSample(const NumericSample& other);
        explicit NumericSample(container_type vec) : container(std::move(vec)) {}
        NumericSample(IDataLoader<std::vector<T>>& loader, std::string filename);
        NumericSample(iterator begin, iterator end);

        NumericSample<T>& operator=(const NumericSample<T>& other);
        NumericSample(NumericSample&& other) noexcept;
        NumericSample<value_type>& operator=(NumericSample<T>&& other) noexcept;

        value_type& operator[](size_t index);
        const value_type& operator[](size_t index) const;

        void push_back(value_type value);
        void add(value_type element);
        void add(container_type elements);
        void remove_at(size_t index);
        const value_type& at(size_type index) const;
        size_type size() const;
        void clear();
        bool empty() const;
        value_type front();
        value_type back();
        void reserve(size_type size);
        size_type capacity();
        void shrink_to_fit();

        value_type min() const;
        value_type max() const;
        value_type arithmetic_mean() const;
        value_type median() const;

        value_type weighted_mean(container_type weights) const;
        value_type geometric_mean() const;
        value_type harmonic_mean() const;
        value_type lower_quartile() const;
        value_type upper_quartile() const;
        auto percentile(double p) const -> std::common_type_t<value_type, double>;
        std::optional<value_type> mode() const;
        std::vector<value_type> modes() const;
        value_type Scope() const;
        value_type interquartile_range() const;
        auto mean_absolute_deviation() const -> std::common_type_t<NumericSample<T>::value_type, double>;

        iterator begin ();
        iterator end ();
        const_iterator begin () const noexcept; 
        const_iterator end () const noexcept; 
        const_iterator cbegin () const noexcept; 
        const_iterator cend () const noexcept; 

    private:
        container_type container;
    };

    template <typename T>
    inline NumericSample<T>::NumericSample(const NumericSample<T> &other)
    {
        this->container = other.container; 
    }

    template <typename T>
    inline NumericSample<T>::NumericSample(IDataLoader<std::vector<T>>& loader, std::string filename)
    {
        container = loader.load(filename);
    }

    template <typename T>
    inline NumericSample<T>::NumericSample(iterator begin, iterator end)
    {
        std::copy(begin, end, std::back_inserter(container));
    }

    template <typename T>
    inline NumericSample<T> &NumericSample<T>::operator=(const NumericSample<T> &other)
    {
        if(this != &other) 
        {
            this->container = other.container;     
        }
        return *this; 
    }

    template <typename T>
    inline NumericSample<T>::NumericSample(NumericSample<T> &&other) noexcept
    {
        this->container = std::move(other.container);
    }

    template <typename T>
    inline NumericSample<T> &NumericSample<T>::operator=(NumericSample<T> &&other) noexcept
    {
        if (this != &other) 
        {
            this->container = std::move(other.container);
        }
        return *this;
    }

    template <typename T>
    inline T &NumericSample<T>::operator[](size_t index)
    {
        return this->container[index];
    }

    template <typename T>
    inline const T &NumericSample<T>::operator[](size_t index) const
    {
        return this->container[index];
    }

    template <typename T>
    inline void NumericSample<T>::push_back(value_type value)
    {
        container.push_back(value);
    }

    template <typename T>
    inline void NumericSample<T>::add(value_type element)
    {
        this->container.push_back(element);
    }

    template <typename T>
    inline void NumericSample<T>::add(container_type elements) 
    {
        this->container.insert(this->container.end(), elements.begin(), elements.end());
    }

    template <typename T>
    inline void NumericSample<T>::remove_at(size_t index)
    {
        this->container.erase(this->container.begin() + index);
    }

    template <typename T>
    inline const T& NumericSample<T>::at(size_type index) const
    {
        return this->container.at(index);
    }

    template <typename T>
    inline size_t NumericSample<T>::size() const
    {
        return this->container.size();
    }

    template <typename T>
    inline void NumericSample<T>::clear()
    {
        this->container.clear();
    }

    template <typename T>
    inline bool NumericSample<T>::empty() const
    {
        return this->container.empty();
    }

    template <typename T>
    inline T NumericSample<T>::front()
    {
        return this->container.front();
    }

    template <typename T>
    inline T NumericSample<T>::back()
    {
        return this->container.back();
    }

    template <typename T>
    inline void NumericSample<T>::reserve(size_type size)
    {
        this->container.reserve(size);
    }

    template <typename T>
    inline size_t NumericSample<T>::capacity()
    {
        return this->capacity();
    }

    template <typename T>
    inline void NumericSample<T>::shrink_to_fit()
    {
        this->container.shrink_to_fit();
    }

    template <typename T>
    inline typename std::vector<T>::iterator NumericSample<T>::begin()
    {
        return this->container.begin();
    }

    template <typename T>
    inline typename std::vector<T>::iterator NumericSample<T>::end()
    {
        return this->container.end();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator NumericSample<T>::begin() const noexcept
    {
        return this->container.cbegin();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator NumericSample<T>::end() const noexcept
    {
        return this->container.cend();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator NumericSample<T>::cbegin() const noexcept
    {
        return this->container.cbegin();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator NumericSample<T>::cend() const noexcept
    {
        return this->container.cend();
    }

    template <typename T>
    inline T NumericSample<T>::min() const
    {
        return nr::min(this->container);
    }

    template <typename T>
    inline T NumericSample<T>::max() const
    {
        return nr::max(this->container);
    }
    template <typename T>
    inline T NumericSample<T>::arithmetic_mean() const
    {
        return nr::arithmetic_mean(this->container);
    }
    template <typename T>
    inline T NumericSample<T>::median() const
    {
        return nr::median(this->container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::geometric_mean() const
    {
        return nr::geometric_mean(container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::harmonic_mean() const
    {
        return nr::harmonic_mean(container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::lower_quartile() const
    {
        return nr::lower_quartile(container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::upper_quartile() const
    {
        return nr::upper_quartile(container);
    }
    template <typename T>
    inline auto NumericSample<T>::percentile(double p) const -> std::common_type_t<NumericSample<T>::value_type, double>
    {
        return nr::percentile(container, p);
    }
    template <typename T>
    inline std::optional<typename NumericSample<T>::value_type> NumericSample<T>::mode() const
    {
        return nr::mode(container);
    }
    template <typename T>
    inline std::vector<typename NumericSample<T>::value_type> NumericSample<T>::modes() const
    {
        return nr::modes(container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::Scope() const
    {
        return nr::Scope(container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::interquartile_range() const
    {
        return nr::interquartile_range(container);
    }
    template <typename T>
    inline auto NumericSample<T>::mean_absolute_deviation() const -> std::common_type_t<NumericSample<T>::value_type, double>
    {
        return nr::mean_absolute_deviation(container);
    }
    template <typename T>
    inline typename NumericSample<T>::value_type NumericSample<T>::weighted_mean(container_type weights) const
    {
        return nr::weighted_mean(container, weights);
    }
}

#endif // NUMERA_CORE_VECTORDATA_H