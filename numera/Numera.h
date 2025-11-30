#ifndef NUMERA_H
#define NUMERA_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <algorithm>
#include<numeric>
#include<cmath>

namespace nr
{
    class Numera
    {
    public:
        Numera(const Numera&) = delete;
        Numera& operator=(const Numera&) = delete;

        Numera(std::string);
        Numera();

        ~Numera();

        void add(double); // add a number to a set
        void add(std::vector<double>); // add a numbers to a set
        size_t count() const; // number of elements
        double min() const; // minimum
        double max() const; // maximum
        double mean() const; // arithmetic mean
        double median() const; // median
        double stddev() const; // standard deviation
        double variance() const; // variance
        bool is_open() const;
        void open_file(std::string);

    private:
        std::vector<double> numbers;
        std::string fileName;
        std::ifstream file;
    };
}
#endif //NUMERA_H