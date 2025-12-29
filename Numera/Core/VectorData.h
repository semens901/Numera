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
 * VectorData is a lightweight wrapper around std::vector that provides
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
    class VectorData
    {
    public:
        //Stores data in std::vector
        using value_type = T;
        using container_type = std::vector<T>;
        using size_type = std::size_t;
        using iterator = typename container_type::iterator;
        using const_iterator =  typename container_type::const_iterator;

        VectorData() = default;
        ~VectorData() = default;
        VectorData(const VectorData& other);
        explicit VectorData(container_type vec) { this->container = vec; }
        VectorData(IDataLoader<std::vector<T>> loader, std::string filename);
        VectorData(iterator begin, iterator end);

        VectorData<T>& operator=(const VectorData<T>& other);
        VectorData(VectorData&& other) noexcept;
        VectorData<value_type>& operator=(VectorData<T>&& other) noexcept;

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
        auto mean_absolute_deviation() const -> std::common_type_t<VectorData<T>::value_type, double>;

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
    inline VectorData<T>::VectorData(const VectorData<T> &other)
    {
        this->container = other.container; 
    }

    template <typename T>
    inline VectorData<T>::VectorData(IDataLoader<std::vector<T>> loader, std::string filename)
    {
        container = loader.load(filename);
    }

    template <typename T>
    inline VectorData<T>::VectorData(iterator begin, iterator end)
    {
        std::copy(begin, end, std::back_inserter(container));
    }

    template <typename T>
    inline VectorData<T> &VectorData<T>::operator=(const VectorData<T> &other)
    {
        if(this != &other) 
        {
            this->container = other.container;     
        }
        return *this; 
    }

    template <typename T>
    inline VectorData<T>::VectorData(VectorData<T> &&other) noexcept
    {
        this->container = std::move(other.container);
    }

    template <typename T>
    inline VectorData<T> &VectorData<T>::operator=(VectorData<T> &&other) noexcept
    {
        if (this != &other) 
        {
            this->container = std::move(other.container);
        }
        return *this;
    }

    template <typename T>
    inline T &VectorData<T>::operator[](size_t index)
    {
        return this->container[index];
    }

    template <typename T>
    inline const T &VectorData<T>::operator[](size_t index) const
    {
        return this->container[index];
    }

    template <typename T>
    inline void VectorData<T>::push_back(value_type value)
    {
        container.push_back(value);
    }

    template <typename T>
    inline void VectorData<T>::add(value_type element)
    {
        this->container.push_back(element);
    }

    template <typename T>
    inline void VectorData<T>::add(container_type elements) 
    {
        this->container.insert(this->container.end(), elements.begin(), elements.end());
    }

    template <typename T>
    inline void VectorData<T>::remove_at(size_t index)
    {
        this->container.erase(this->container.begin() + index);
    }

    template <typename T>
    inline const T& VectorData<T>::at(size_type index) const
    {
        return this->container.at(index);
    }

    template <typename T>
    inline size_t VectorData<T>::size() const
    {
        return this->container.size();
    }

    template <typename T>
    inline void VectorData<T>::clear()
    {
        this->container.clear();
    }

    template <typename T>
    inline bool VectorData<T>::empty() const
    {
        return this->container.empty();
    }

    template <typename T>
    inline T VectorData<T>::front()
    {
        return this->container.front();
    }

    template <typename T>
    inline T VectorData<T>::back()
    {
        return this->container.back();
    }

    template <typename T>
    inline void VectorData<T>::reserve(size_type size)
    {
        this->container.reserve(size);
    }

    template <typename T>
    inline size_t VectorData<T>::capacity()
    {
        return this->capacity();
    }

    template <typename T>
    inline void VectorData<T>::shrink_to_fit()
    {
        this->container.shrink_to_fit();
    }

    template <typename T>
    inline typename std::vector<T>::iterator VectorData<T>::begin()
    {
        return this->container.begin();
    }

    template <typename T>
    inline typename std::vector<T>::iterator VectorData<T>::end()
    {
        return this->container.end();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator VectorData<T>::begin() const noexcept
    {
        return this->container.cbegin();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator VectorData<T>::end() const noexcept
    {
        return this->container.cend();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator VectorData<T>::cbegin() const noexcept
    {
        return this->container.cbegin();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator VectorData<T>::cend() const noexcept
    {
        return this->container.cend();
    }

    template <typename T>
    inline T VectorData<T>::min() const
    {
        return nr::min(this->container);
    }

    template <typename T>
    inline T VectorData<T>::max() const
    {
        return nr::max(this->container);
    }
    template <typename T>
    inline T VectorData<T>::arithmetic_mean() const
    {
        return nr::arithmetic_mean(this->container);
    }
    template <typename T>
    inline T VectorData<T>::median() const
    {
        return nr::median(this->container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::geometric_mean() const
    {
        return nr::geometric_mean(container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::harmonic_mean() const
    {
        return nr::harmonic_mean(container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::lower_quartile() const
    {
        return nr::lower_quartile(container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::upper_quartile() const
    {
        return nr::upper_quartile(container);
    }
    template <typename T>
    inline auto VectorData<T>::percentile(double p) const -> std::common_type_t<VectorData<T>::value_type, double>
    {
        return nr::percentile(container, p);
    }
    template <typename T>
    inline std::optional<typename VectorData<T>::value_type> VectorData<T>::mode() const
    {
        return nr::mode(container);
    }
    template <typename T>
    inline std::vector<typename VectorData<T>::value_type> VectorData<T>::modes() const
    {
        return nr::modes(container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::Scope() const
    {
        return nr::Scope(container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::interquartile_range() const
    {
        return nr::interquartile_range(container);
    }
    template <typename T>
    inline auto VectorData<T>::mean_absolute_deviation() const -> std::common_type_t<VectorData<T>::value_type, double>
    {
        return nr::mean_absolute_deviation(container);
    }
    template <typename T>
    inline typename VectorData<T>::value_type VectorData<T>::weighted_mean(container_type weights) const
    {
        return nr::weighted_mean(container, weights);
    }
}

#endif // NUMERA_CORE_VECTORDATA_H