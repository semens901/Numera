#include<iostream>
#include "numera.h"
#include "sampling/sampling.h"
#include <cassert>

int main()
{
    nr::Numera nm("numbers.txt");
    if(!nm.is_open())
        return 1;
    std::cout << "Count:\t" << nm.count() << std::endl;
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
    }

    {
        std::vector<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t step = 3;
        auto sample = nr::Sampling::systematic(stats, step);

        
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        std::vector<double> stats({10,11,12, 20,21,22, 30,31,32, 40,41});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1, 0,0,0, 2,2,2, 3,3};
        size_t samplePerStratum = 2;

        auto strat = nr::Sampling::stratified(stats, labels, samplePerStratum);

        std::cout << "Stratified sample (" << strat.size() << "):";
        for (double v : strat) std::cout << ' ' << v;
        std::cout << '\n';
    }

    return 0;
}