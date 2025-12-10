#ifndef NUMERA_CORE_VECTORDATA_H
#define NUMERA_CORE_VECTORDATA_H

#include "DataSet.h"

namespace nr
{   
    template <typename T>
    class VectorData : public DataSet<std::vector<T>>
    {
    public:

        using value_type = T;
        using container_type = std::vector<T>;
        using size_type = std::size_t;

        VectorData() = default;
        ~VectorData() override = default;
        VectorData(const VectorData& other);
        VectorData(container_type vec) { this->container = std::move(vec); }

        VectorData<T>& operator=(const VectorData<T>& other);
        VectorData(VectorData&& other) noexcept;
        VectorData<value_type>& operator=(VectorData<T>&& other) noexcept;

        value_type& operator[](size_t index);
        const value_type& operator[](size_t index) const;

        void add(value_type element) override;
        void add(container_type elements);
        void remove_at(size_t index) override;
        const value_type& at(size_type index) const override;
        size_type size() const override;
        void clear() override;
        bool empty() const override;

        typename container_type::iterator begin () override;
        typename container_type::iterator end () override;
        typename container_type::const_iterator cbegin () const noexcept override; 
        typename container_type::const_iterator cend () const noexcept override; 

    };

    template <typename T>
    inline VectorData<T>::VectorData(const VectorData<T> &other)
    {
        this->container = other.container; 
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
}

#endif // NUMERA_CORE_VECTORDATA_H