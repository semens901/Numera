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
        VectorData(container_type vec) { this->container = vec; }
        VectorData(IDataLoader<std::vector<T>> loader, std::string filename);

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

        value_type min() const;
        value_type max() const;
        value_type mean() const;
        value_type median() const;

        iterator begin ();
        iterator end ();
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
    inline const T& VectorData<T>::at(size_t index) const
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
    inline T VectorData<T>::mean() const
    {
        return nr::mean(this->container);
    }
    template <typename T>
    inline T VectorData<T>::median() const
    {
        return nr::median(this->container);
    }
}

#endif // NUMERA_CORE_VECTORDATA_H