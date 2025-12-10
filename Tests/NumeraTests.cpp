#include "Core/VectorData.h"
#include "io/CsvDataLoader.h"
#include "stats/Sampling.h"
#include "stats/BasicStats.h"
#include "io/FileDataLoader.h"

#include<iostream>
#include<cassert>
#include<string>

// helper: comparison of doubles taking into account the error
bool almostEqual(double a, double b, double eps = 1e-9)
{
    return std::abs(a - b) < eps;
}

int main()
{
    {
        std::cout << "[TEST] Adding elements\n";

        nr::VectorData<double> vd;
        vd.add(10.0);
        vd.add(20.0);
        vd.add(30.0);

        assert(vd.size() == 3);
        std::cout << "Test passed: size is " << vd.size() << "\n";
    }

    {
        std::cout << "[TEST] Adding elements\n";
        nr::VectorData<double> vd;
        vd.add({1.0, 2.0, 3.0, 4.0, 5.0});
        assert(vd.size() == 5);
        std::cout << "Test passed: size is " << vd.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::VectorData<double> vd2 = vd; // copy constructor
        assert(vd2.size() == 5);    
        std::cout << "Test passed: size is " << vd2.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::VectorData<double> vd3;
        vd3 = vd; // copy assignment
        assert(vd3.size() == 5);    
        std::cout << "Test passed: size is " << vd3.size() << "\n";

        std::cout << "[TEST] Move semantics\n";
        nr::VectorData<double> vd4 = std::move(vd); // move constructor
        assert(vd4.size() == 5);
        assert(vd.size() == 0); // vd should be empty after move
        std::cout << "Test passed: size is " << vd4.size() << "\n";    
        
        std::cout << "[TEST] Move semantics\n";
        nr::VectorData<double> vd5;
        vd5 = std::move(vd2); // move assignment
        assert(vd5.size() == 5);
        assert(vd2.size() == 0); // vd2 should be empty after move
        std::cout << "Test passed: size is " << vd5.size() << "\n";

        std::cout << "[TEST] Removing elements\n";
        nr::VectorData<double> vd6({1,2,3});
        vd6.remove_at(1); // remove element at index 1
        assert(vd6.size() == 2);
        assert(vd6[0] == 1);
        assert(vd6[1] == 3);
        std::cout << "Test passed: size is " << vd6.size() << "\n";
    }

    {
        std::cout << "[TEST] Minimum and maximum\n";

        nr::VectorData<double> vd;
        vd.add({5, 10, 2, 8});

        assert(min(vd) == 2);
        assert(max(vd) == 10);
    }

    {
        std::cout << "[TEST] Simple random sampling\n";

        nr::VectorData<double> stats({10, 20, 30, 40, 50});

        size_t sampleSize = 3;
        auto sample = nr::Sampling::simple_random(stats, sampleSize);

        assert(sample.size() == sampleSize);
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::Sampling::systematic(stats, sample);

        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
        assert(sampleResult.size() == static_cast<double>(std::ceil(step)));
    }

    {
        std::cout << "[TEST] Systematic sorted sampling\n";
        std::vector<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::Sampling::systematic_sorted(stats, sample);

        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
        assert(sampleResult.size() == static_cast<double>(std::ceil(step)));
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        std::vector<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        auto strat = nr::Sampling::stratified(stats, labels, sampleSize);

        assert(strat.size() == sampleSize);
    }

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
