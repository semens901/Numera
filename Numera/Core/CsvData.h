#ifndef CSVDATA_H
#define CSVDATA_H
#include "stats/BasicStats.h"

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<cmath>

namespace nr
{
    template<typename key_type, typename data_type>
    class CSVDataStore
    {
    public:
        using container_type = std::map<key_type, std::vector<data_type>>;
        using vector_type = typename std::vector<data_type>;
        using size_type = std::size_t;
        using iterator = typename container_type::iterator;
        using const_iterator =  typename container_type::const_iterator;

        CSVDataStore() = default;
        CSVDataStore(const CSVDataStore& other) = default;
        CSVDataStore& operator=(const CSVDataStore& other) = default;
        CSVDataStore(CSVDataStore&& other) noexcept = default;
        CSVDataStore& operator=(CSVDataStore&& other) noexcept = default;
        ~CSVDataStore() = default;

        CSVDataStore(std::initializer_list<
    std::pair<const key_type, std::vector<data_type>>> init);

        CSVDataStore& operator=(std::initializer_list<
    std::pair<const key_type, std::vector<data_type>>> init);

        CSVDataStore(std::map<key_type, std::vector<data_type>> data);

        vector_type& operator[](const key_type& key);
        const vector_type& operator[](const key_type& key) const;

        void add(const key_type& key, data_type value);
        const vector_type& at(key_type key) const;
        size_type size() const;
        void clear();
        bool empty() const;
        void remove_at(key_type key);

        data_type min() const;
        data_type max() const;
        data_type mean() const;
        data_type median() const;

        iterator begin();
        iterator end();
        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        void remove_at(iterator it);
        void remove_at(iterator it_begin, iterator it_end);
        
    private:
        container_type container;
    };

    template <typename key_type, typename data_type>
    inline CSVDataStore<key_type, data_type>::CSVDataStore(std::initializer_list<std::pair<const key_type, std::vector<data_type>>> init)
    {
        for (const auto& [key, vec] : init)
        this->container[key] = vec;
    }

    template <typename key_type, typename data_type>
    inline CSVDataStore<key_type, data_type> &CSVDataStore<key_type, data_type>::operator=(std::initializer_list<std::pair<const key_type, std::vector<data_type>>> init)
    {
        container.clear();
        for (const auto& [key, vec] : init)
        this->container[key] = vec;
        return *this;
    }

    template <typename key_type, typename data_type>
    inline CSVDataStore<key_type, data_type>::CSVDataStore(std::map<key_type, std::vector<data_type>> data)
    {
        container = data;
    }

    template <typename key_type, typename data_type>
    inline std::vector<data_type> &CSVDataStore<key_type, data_type>::operator[](const key_type &key)
    {
        return container[key];
    }

    template <typename key_type, typename data_type>
    inline const std::vector<data_type> &CSVDataStore<key_type, data_type>::operator[](const key_type &key) const
    {
        return container.at(key);
    }

    template <typename key_type, typename data_type>
    inline void CSVDataStore<key_type, data_type>::add(const key_type &key, data_type value)
    {
        container[key].push_back(value);
    }

    template <typename key_type, typename data_type>
    inline const std::vector<data_type> &CSVDataStore<key_type, data_type>::at(key_type key) const
    {
        return container.at(key);
    }

    template <typename key_type, typename data_type>
    inline size_t CSVDataStore<key_type, data_type>::size() const
    {
        return container.size();
    }

    template <typename key_type, typename data_type>
    inline void CSVDataStore<key_type, data_type>::clear()
    {
        container.clear();
    }

    template <typename key_type, typename data_type>
    inline bool CSVDataStore<key_type, data_type>::empty() const
    {
        return container.empty();
    }

    template <typename key_type, typename data_type>
    inline void CSVDataStore<key_type, data_type>::remove_at(key_type key)
    {
        container.erase(key);
    }

    template <typename key_type, typename data_type>
    inline data_type CSVDataStore<key_type, data_type>::min() const
    {
        return nr::min(container);
    }

    template <typename key_type, typename data_type>
    inline data_type CSVDataStore<key_type, data_type>::max() const
    {
        return nr::max(container);
    }

    template <typename key_type, typename data_type>
    inline data_type CSVDataStore<key_type, data_type>::mean() const
    {
        return 1;
    }

    template <typename key_type, typename data_type>
    inline data_type CSVDataStore<key_type, data_type>::median() const
    {
        return 1;
    }

    template <typename key_type, typename data_type>
    inline typename std::map<key_type, std::vector<data_type>>::iterator CSVDataStore<key_type, data_type>::begin()
    {
        return container.begin();
    }

    template <typename key_type, typename data_type>
    inline typename std::map<key_type, std::vector<data_type>>::iterator CSVDataStore<key_type, data_type>::end()
    {
        return container.end();
    }

    template <typename key_type, typename data_type>
    inline typename std::map<key_type, std::vector<data_type>>::const_iterator CSVDataStore<key_type, data_type>::begin() const noexcept
    {
        return container.begin();
    }

    template <typename key_type, typename data_type>
    inline typename std::map<key_type, std::vector<data_type>>::const_iterator CSVDataStore<key_type, data_type>::end() const noexcept
    {
        return container.end();
    }

    template <typename key_type, typename data_type>
    inline typename std::map<key_type, std::vector<data_type>>::const_iterator CSVDataStore<key_type, data_type>::cbegin() const noexcept
    {
        return container.cbegin();
    }

    template <typename key_type, typename data_type>
    inline typename std::map<key_type, std::vector<data_type>>::const_iterator CSVDataStore<key_type, data_type>::cend() const noexcept
    {
        return container.cend();
    }
    template <typename key_type, typename data_type>
    inline void CSVDataStore<key_type, data_type>::remove_at(iterator it)
    {
        container.erase(it);
    }
    template <typename key_type, typename data_type>
    inline void CSVDataStore<key_type, data_type>::remove_at(iterator it_begin, iterator it_end)
    {
        container.erase(it_begin, it_end);
    }
}

#endif // CSVDATA_H