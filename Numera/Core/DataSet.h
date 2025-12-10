#ifndef NUMERA_H
#define NUMERA_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<cmath>

namespace nr
{
    template <class Container>  
    class DataSet
    {
    public:

        using value_type = typename Container::value_type;
        using container_type = Container;
        using size_type = std::size_t;
        using iterator = typename container_type::iterator;
        using const_iterator =  typename container_type::const_iterator;

        DataSet() = default;
        DataSet(const DataSet& other) = default;
        DataSet(Container cont) : container(std::move(cont)) {}
        DataSet& operator=(const DataSet& other) = default;
        DataSet(DataSet&& other) noexcept = default;
        DataSet& operator=(DataSet&& other) noexcept = default;

        virtual ~DataSet() = default;

        virtual void add(double) = 0;
        virtual const value_type& at(size_type index) const = 0;
        virtual size_type size() const = 0;
        virtual void clear() = 0;
        virtual bool empty() const = 0;
        virtual void remove_at(size_t index) = 0;
    
        virtual iterator begin() = 0;
        virtual iterator end() = 0;
        virtual const_iterator cbegin() const noexcept = 0;
        virtual const_iterator cend() const noexcept = 0;

    protected:
        Container container;
    };
}
#endif //NUMERA_H