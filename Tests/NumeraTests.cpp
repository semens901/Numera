#include <cassert>
#include <iostream>
#include "Numera.h"
#include "Sampling/Sampling.h"

// helper: comparison of doubles taking into account the error
bool almostEqual(double a, double b, double eps = 1e-9)
{
    return std::abs(a - b) < eps;
}

int main()
{
    {
        std::cout << "[TEST] Adding elements\n";

        nr::Numera stats;
        stats.add(10.0);
        stats.add(20.0);
        stats.add(30.0);

        assert(stats.size() == 3);
    }

    {
        std::cout << "[TEST] Minimum and maximum\n";

        nr::Numera stats;
        stats.add({5, 10, 2, 8});

        assert(stats.min() == 2);
        assert(stats.max() == 10);
    }

    {
        std::cout << "[TEST] Checking the average\n";

        nr::Numera stats;
        stats.add({1, 2, 3, 4, 5});

        assert(almostEqual(stats.mean(), 3.0));
    }

    {
        std::cout << "[TEST] Checking the median (odd number)\n";

        nr::Numera stats;
        stats.add({3, 1, 5});

        assert(almostEqual(stats.median(), 3.0));
    }

    {
        std::cout << "[TEST] Median (even number)\n";

        nr::Numera stats;
        stats.add({4, 2, 8, 6});

        // sorted: 2,4,6,8 -> median = (4+6)/2 = 5
        assert(almostEqual(stats.median(), 5.0));
    }

    {
        std::cout << "[TEST] Variance and standard deviation\n";

        nr::Numera stats;
        stats.add({1, 2, 3, 4, 5});
        // variance = 2, stddev = sqrt(2)
        //assert(almostEqual(stats.variance(), 2.0));
        assert(almostEqual(stats.stddev(), std::sqrt(2.5)));
    }

    {
        std::cout << "[TEST] Simple random sampling\n";

        std::vector<double> stats({10, 20, 30, 40, 50});

        size_t sampleSize = 3;
        auto sample = nr::Sampling::simple_random(stats, sampleSize);

        assert(sample.size() == sampleSize);
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        std::vector<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

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
