#include "Core/VectorData.h"
#include "io/CsvDataLoader.h"
#include "stats/ProbabilitySampling.h"
#include "io/FileDataLoader.h"
#include "Core/CsvData.h"
#include "stats/NonProbabilitySampling.h"

#include<iostream>
#include<cassert>
#include<string>

int main()
{    
    CSVDataLoader store("example.csv");

    {
        nr::CSVData<std::string, double> csv;
        FileDataLoader file_loader;
        nr::VectorData<double> dt(file_loader.load("numbers.txt"));
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;
    }

    {
        nr::CSVData<std::string, double> csv(std::map<std::string, std::vector<double>>{{"hello", {1,2,3}},{"hi", {0,4,5}}});
        std::cout << "Min:\t" << "(" << csv.min() << ")" << std::endl; 
        std::cout << "Max:\t" << "(" << csv.max() << ")" << std::endl;
    }

    {
        std::cout << "[TEST] Simple random sampling\n";

        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sampleSize = 5;
        auto sample = nr::ProbabilitySampling::simple_random<double>(stats, sampleSize);

        assert(sample.size() == sampleSize);

        std::cout << "Simple random sample (" << sample.size() << "):";
        for (double v : sample) std::cout << ' ' << v;
        std::cout << '\n';

        nr::CSVData<std::string, double> cd{std::map<std::string, std::vector<double>>
        {
            {"Test1", {1, 2, 5,3}},
            {"Test2", {0, 12, 14}},
            {"Test3", {15, 90, 84, 15}}
        }};

        std::vector<double> res = nr::ProbabilitySampling::simple_random<std::string, double>(cd, sampleSize);
        std::cout << "SAMPLE SIZE\t" << res.size() << "\n";
        assert(res.size() == sampleSize);
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

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

    {
        std::cout << "[TEST] Quota sampling (CSVData with quotas)\n";

        nr::CSVData<std::string, double> cv;
        cv["A"] = {1, 2, 3};
        cv["B"] = {10, 20, 30, 40};
        cv["C"] = {100, 200};

        std::unordered_map<std::string, size_t> quotas = {
            {"A", 2},
            {"B", 3},
            {"C", 1}
        };

        auto quotaSample = nr::NonProbabilitySampling::quotaSample(cv, quotas);

        // Checking the total sample size
        assert(quotaSample.size() == 6); // 2+3+1=6

        // We check that the elements are actually taken from the original groups
        for (auto v : quotaSample) {
            bool inA = std::find(cv["A"].begin(), cv["A"].end(), v) != cv["A"].end();
            bool inB = std::find(cv["B"].begin(), cv["B"].end(), v) != cv["B"].end();
            bool inC = std::find(cv["C"].begin(), cv["C"].end(), v) != cv["C"].end();
            assert(inA || inB || inC);
        }

        // Test: Empty CSVData
        nr::CSVData<std::string, double> emptyCv;
        std::unordered_map<std::string, size_t> quotasEmpty = { {"A", 1} };
        auto emptySample = nr::NonProbabilitySampling::quotaSample(emptyCv, quotasEmpty);
        assert(emptySample.size() == 0);

        // Test: Quota exceeds the number of elements in the group
        nr::CSVData<std::string, double> smallCv;
        smallCv["X"] = {5, 6};
        std::unordered_map<std::string, size_t> quotasExceed = { {"X", 5} };
        auto exceedSample = nr::NonProbabilitySampling::quotaSample(smallCv, quotasExceed);
        assert(exceedSample.size() == 2);
        for (auto v : exceedSample)
            assert(v == 5 || v == 6);
    }

    {
         std::cout << "[TEST] Haphazard sampling (CSVData)\n";

        nr::CSVData<std::string, double> cv;
        cv["A"] = {1, 2, 3};
        cv["B"] = {10, 20, 30, 40};
        cv["C"] = {100, 200};

        // --- Тест 1: обычная выборка ---
        size_t sampleSize = 5;
        auto haphazard = nr::NonProbabilitySampling::haphazardSample(cv, sampleSize);

        assert(haphazard.size() == sampleSize);
    }


    return 0;
}