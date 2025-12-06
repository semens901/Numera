#ifndef SAMPLING_H
#define SAMPLING_H
#include<vector>
#include "numera.h"
#include<random>
#include<algorithm>

namespace nr
{
    class Sampling {
    public:
        static std::vector<double> simple_random(
            const std::vector<double>& data,
            size_t sampleSize
        );

        static std::vector<double> systematic(
            const std::vector<double>& data,
            size_t step
        );

        static std::vector<double> systematic_sorted(
            const std::vector<double>& data,
            size_t step
        );

        static std::vector<double> stratified(
            const std::vector<double>& data,
            const std::vector<size_t>& strataLabels,
            size_t samplePerStratum
        );
//////////////////////////////////////////////////////////
        static std::vector<double> simple_random(
            const Numera& data,
            size_t sampleSize
        );

        static std::vector<double> systematic(
            const Numera& data,
            size_t step
        );

        static std::vector<double> stratified(
            const Numera& data,
            const std::vector<size_t>& strataLabels,
            size_t samplePerStratum
        );

    };
}

#endif // SAMPLING_H