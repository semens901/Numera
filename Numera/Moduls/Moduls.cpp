#include "Moduls.h"

bool nr::Moduls::almostEqual(double a, double b, double eps)
{
    return std::abs(a - b)
        <= eps * std::max(std::abs(a), std::abs(b));
}