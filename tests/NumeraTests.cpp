#include <cassert>
#include <iostream>
#include "Numera.h"

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

        assert(stats.count() == 3);
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

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
