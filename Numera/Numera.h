#ifndef NUMERA_H
#define NUMERA_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<cmath>
#include "FileDataLoader.h"

namespace nr
{
    class Numera
    {
    public:
        Numera(const Numera&);
        Numera& operator=(const Numera&);

        Numera(std::string, IDataLoader&);
        Numera(std::vector<double>);
        Numera();

        ~Numera();

        void add(double); // add a number to a set
        void add(std::vector<double>); // add a numbers to a set

        double& operator[](size_t);
        const double& operator[](size_t) const;

        double at(size_t) const;
        double front() const;
        double back() const;
        void clear();
        bool empty() const;

        void pop_back();
        void remove_at(size_t);

        void load_data(const std::string&, IDataLoader&);
        void save_data(const std::string&, IDataLoader&) const;

        size_t size() const; // number of elements
        double min() const; // minimum
        double max() const; // maximum
        double mean() const; // arithmetic mean
        double median() const; // median
        double stddev() const; // standard deviation
        double variance() const; // variance
    
        std::vector<double>::iterator begin ();
        std::vector<double>::iterator end ();
        std::vector<double>::const_iterator begin () const; 
        std::vector<double>::const_iterator end () const; 

    private:
        std::vector<double> numbers;
        std::string fileName;
    };
}
#endif //NUMERA_H