#include<iostream>
#include "numera.h"
#include "sampling/sampling.h"
#include <cassert>

int main()
{
    nr::Numera nm("numbers.txt");
    if(!nm.is_open())
        return 1;
    std::cout << "Count:\t" << nm.size() << std::endl;
    std:: cout << "Min:\t" << nm.min() << std::endl;
    std:: cout << "Max:\t" << nm.max() << std::endl;
    std:: cout << "Arithmetic mean:\t" << nm.mean() << std::endl;
    std:: cout << "Median:\t" << nm.median() << std::endl;
    std:: cout << "Standard deviation:\t" << nm.stddev() << std::endl;
    
    {
        std::cout << "[TEST] Simple random sampling\n";

        std::vector<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sampleSize = 5;
        auto sample = nr::Sampling::simple_random(stats, sampleSize);

        assert(sample.size() == sampleSize);

        std::cout << "Simple random sample (" << sample.size() << "):";
        for (double v : sample) std::cout << ' ' << v;
        std::cout << '\n';
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        std::vector<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::Sampling::systematic(stats, sample);

        std::cout << "Systematic sample (" << sampleResult.size() << "):";
        for (double v : sampleResult) std::cout << ' ' << v;
        std::cout << '\n';
        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
    }

    {
        std::cout << "[TEST] Systematic sorted sampling\n";
        std::vector<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::Sampling::systematic_sorted(stats, sample);

        std::cout << "Systematic sorted sample (" << sampleResult.size() << "):";
        for (double v : sampleResult) std::cout << ' ' << v;
        std::cout << '\n';
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        std::vector<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        auto strat = nr::Sampling::stratified(stats, labels, sampleSize);

        std::cout << "Stratified sample (" << strat.size() << "):";
        for (double v : strat) std::cout << ' ' << v;
        std::cout << '\n';
    }

    return 0;
}