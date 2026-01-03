#include "Core/NumericSample.h"
#include "io/CsvDataLoader.h"
#include "stats/ProbabilitySampling.h"
#include "io/FileDataLoader.h"
#include "stats/NonProbabilitySampling.h"

#include<iostream>
#include<cassert>
#include<string>

int main()
{    
    //CSVDataLoader store("example.csv");

   /* {
        nr::CSVTable<std::string, double> csv;
        FileDataLoader file_loader;
        nr::NumericSample<double> dt(file_loader.load("numbers.txt"));
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;
    }
    */

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::NumericSample<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::ProbabilitySampling::systematic<double>(stats, sample);

        std::cout << "Systematic sample (" << sampleResult.size() << "):";
        for (double v : sampleResult) std::cout << ' ' << v;
        std::cout << '\n';
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        std::vector<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        auto strat = nr::ProbabilitySampling::stratified<double>(stats, labels, sampleSize);

        std::cout << "Stratified sample (" << strat.size() << "):";
        for (double v : strat) std::cout << ' ' << v;
        std::cout << '\n';
    }


    return 0;
}