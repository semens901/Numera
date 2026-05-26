#ifndef MODULS_H
#define MODULS_H
#include<cmath>
namespace nr
{
    // Utility class for numeric comparisons and tolerance values.
    class Moduls
    {
    public:
        Moduls() = delete;
        // Return true if `a` and `b` differ by no more than `eps`.
        static bool almostEqual(double a, double b, double eps);

        // Default tolerances for comparisons (small to large).
        static constexpr double DEFAULT_EPS = 1e-9;
        static constexpr double DEFAULT_EPS_LARGE = 1e-6;
        static constexpr double DEFAULT_EPS_SMALL = 1e-12;
        static constexpr double DEFAULT_EPSILON = 0.0001;
    };
}

#endif // MODULS_H