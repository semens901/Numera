#include "ProbabilitySamplingTests.h"

void probability_sampling_tests()
{
    {
        std::cout << "[TEST] Simple random sampling\n";

        nr::VectorData<double> stats({10, 20, 30, 40, 50});

        size_t sampleSize = 3;
        auto sample = nr::ProbabilitySampling::simple_random<double>(stats, sampleSize);

        assert(sample.size() == sampleSize);

        nr::VectorData<double> emptyStats;
        std::vector<double> emptySample = nr::ProbabilitySampling::simple_random<double>(emptyStats, sampleSize);
        assert(emptySample.size() == 0);

        nr::CSVData<std::string, double> cd{std::map<std::string, std::vector<double>>
        {
            {"Test1", {1, 2, 5,3}},
            {"Test2", {0, 12, 14}},
            {"Test3", {15, 90, 84, 15}}
        }};

        std::vector<double> res = nr::ProbabilitySampling::simple_random<std::string, double>(cd, sampleSize);
        std::cout << "SAMPLE SIZE\t" << res.size();
        assert(res.size() == sampleSize);

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::ProbabilitySampling::systematic<double>(stats, sample);

        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
        assert(sampleResult.size() == static_cast<double>(std::ceil(step)));

        nr::VectorData<double> emptyStats;
        auto emptySample = nr::ProbabilitySampling::systematic<double>(emptyStats, sample);
        assert(emptySample.size() == 0);
        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        nr::VectorData<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        std::vector<double> strat = nr::ProbabilitySampling::stratified<double>(stats, labels, sampleSize);

        assert(strat.size() == sampleSize);

        nr::CSVData<std::string, double> cv;
        cv["1"] = {10,11,12,13};
        cv["0"] = {20, 21, 22, 23, 24};
        cv["2"] = {2, 2, 2};
        cv["3"] = {40, 41, 42, 43, 44, 45};

        auto strat1 = nr::ProbabilitySampling::stratified<std::string, double>(cv, 5);

        assert(strat1.size() == 5);


        size_t sampleSize1 = 8;
        std::vector<double> emptyStats1;
        std::vector<size_t> emptyLabels1;
        auto emptySample1 = nr::ProbabilitySampling::stratified<double>(emptyStats1, emptyLabels1, sampleSize);
        assert(emptySample1.size() == 0);
        std::cout << "[TEST] successfully!\n";
    }

}