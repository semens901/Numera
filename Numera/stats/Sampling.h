#ifndef SAMPLING_H
#define SAMPLING_H
#include "RandomGenerator/RandomValueGenerator.h"

#include<vector>
#include<random>
#include<algorithm>
#include <chrono>
#include <unordered_map>
#include<iostream>
#include<cmath>
#include "Core/DataSet.h"

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
            size_t sample
        );

        static std::vector<double> systematic_sorted(
            const std::vector<double>& data,
            size_t sample
        );

        static std::vector<double> stratified(
            const std::vector<double>& data,
            const std::vector<size_t>& strataLabels,
            size_t samplePerStratum
        );
////////////////////////////////////////////////////

        static std::vector<double> simple_random(
            const nr::DataSet<std::vector<double>>& data,
            size_t sampleSize
        );

        static std::vector<double> systematic(
            const nr::DataSet<std::vector<double>>& data,
            size_t sample
        );

        static std::vector<double> systematic_sorted(
            const nr::DataSet<std::vector<double>>& data,
            size_t sample
        );
        /*
        static std::vector<double> stratified(
            const std::vector<double>& data,
            const std::vector<size_t>& strataLabels,
            size_t samplePerStratum
        );
        */
    };
}

#endif // SAMPLING_H