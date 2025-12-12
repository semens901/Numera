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
#include "Core/VectorData.h"
#include "Core/CsvData.h"

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

        static std::vector<double> stratified(
            const std::vector<double>& data,
            const std::vector<size_t>& strataLabels,
            size_t samplePerStratum
        );

////////////////////////////////////////////////////

        static std::vector<double> simple_random(
            const nr::VectorData<double>& data,
            size_t sampleSize
        );

        static std::vector<double> systematic(
            const nr::VectorData<double>& data,
            size_t sample
        );
        
        static std::vector<double> stratified(
            const nr::VectorData<double>& data,
            const std::vector<size_t>& strataLabels,
            size_t sampleSize
        );

////////////////////////////////////////////////////

        static std::vector<double> simple_random(
            const nr::CSVDataStore<std::string, double>& data,
            size_t sampleSize
        );

        static std::vector<double> systematic(
            const nr::CSVDataStore<std::string, double>& data,
            size_t sample
        );
        
        static std::vector<double> stratified(
            const nr::CSVDataStore<std::string, double>& data,
            size_t sampleSize
        );
    };
}

#endif // SAMPLING_H