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

        VectorData(const VectorData& other) : vec(other.vec) {};
        VectorData(container_type vec)  : vec(vec) {}

        VectorData<T>& operator=(const VectorData& other);
        VectorData(VectorData&& other) noexcept : vec(std::move(other.vec)){};
        VectorData<value_type>& operator=(VectorData&& other) noexcept;

        value_type& operator[](size_t index);
        const value_type& operator[](size_t index) const;

        void add(value_type element) override;
        void add(container_type elements);
        void remove_at(size_t index) override;
        const value_type& at(size_type index) const override;
        size_type size() const override;
        void clear() override;
        bool empty() const override;

        typename container_type::iterator begin ();
        typename container_type::iterator end ();
        typename container_type::const_iterator cbegin () const noexcept; 
        typename container_type::const_iterator cend () const noexcept; 


    private:
        container_type vec;
    };

    template <typename T>
    inline VectorData<T> &VectorData<T>::operator=(const VectorData &other)
    {
        if(this != &other) 
        {
            this->vec = other.vec;     
        }
        return *this; 
    }

    template <typename T>
    inline VectorData<T> &VectorData<T>::operator=(VectorData &&other) noexcept
    {
        if (this != &other) 
        {
            this->vec = std::move(other.vec);
        }
        return *this;
    }

    template <typename T>
    inline T &VectorData<T>::operator[](size_t index)
    {
        return vec[index];
    }

    template <typename T>
    inline const T &VectorData<T>::operator[](size_t index) const
    {
        return vec[index];
    }

    template <typename T>
    inline void VectorData<T>::add(value_type element)
    {
        vec.push_back(element);
    }

    template <typename T>
    inline void VectorData<T>::add(container_type elements) 
    {
        vec.insert(vec.end(), elements.begin(), elements.end());
    }

    template <typename T>
    inline void VectorData<T>::remove_at(size_t index)
    {
        vec.erase(vec.begin() + index);
    }

    template <typename T>
    inline const T& VectorData<T>::at(size_t index) const
    {
        return vec.at(index);
    }

    template <typename T>
    inline size_t VectorData<T>::size() const
    {
        return vec.size();
    }

    template <typename T>
    inline void VectorData<T>::clear()
    {
        vec.clear();
    }

    template <typename T>
    inline bool VectorData<T>::empty() const
    {
        return vec.empty();
    }

    template <typename T>
    inline typename std::vector<T>::iterator VectorData<T>::begin()
    {
        return vec.begin();
    }

    template <typename T>
    inline typename std::vector<T>::iterator VectorData<T>::end()
    {
        return vec.end();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator VectorData<T>::cbegin() const noexcept
    {
        return vec.cbegin();
    }

    template <typename T>
    inline typename std::vector<T>::const_iterator VectorData<T>::cend() const noexcept
    {
        return vec.cend();
    }
}

#endif // NUMERA_CORE_VECTORDATA_H