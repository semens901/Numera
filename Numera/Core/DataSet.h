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
        using size_type = std::size_t;

        virtual ~DataSet() = default;

        virtual void add(double) = 0;
        virtual const value_type& at(size_t index) const = 0;
        virtual size_type size() const = 0;
        virtual void clear() = 0;
        virtual bool empty() const = 0;
        virtual void remove_at(size_t index) = 0;
    };
}
#endif //NUMERA_H