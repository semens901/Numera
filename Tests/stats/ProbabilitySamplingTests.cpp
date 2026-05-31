#include "ProbabilitySamplingTests.h"

void probability_sampling_tests()
{
    ProbabilitySampling_SimpleRandom_tests();

    ProbabilitySampling_Systematic_tests();

    ProbabilitySampling_Stratified_tests();

}

void ProbabilitySampling_SimpleRandom_tests()
{
    ProbabilitySampling_ContainerSimpleRandom_test();
    ProbabilitySampling_IteratorSimpleRandom_test();
}

void ProbabilitySampling_ContainerSimpleRandom_test()
{
    {
        nr::NumericSample<double> stats({10, 20, 30, 40, 50});

        size_t sampleSize = 3;
        auto sample = nr::ProbabilitySampling::simple_random(stats, sampleSize);

        assert(sample.size() == sampleSize);

        nr::NumericSample<double> emptyStats;
        std::vector<double> emptySample = nr::ProbabilitySampling::simple_random(emptyStats, sampleSize);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] Simple random sampling successfully!\n";
    }
}

void ProbabilitySampling_IteratorSimpleRandom_test()
{
    {
        nr::NumericSample<double> stats({10, 20, 30, 40, 50});

        size_t sampleSize = 3;
        auto sample = nr::ProbabilitySampling::simple_random(stats.begin(), stats.end(), sampleSize);

        assert(sample.size() == sampleSize);

        nr::NumericSample<double> emptyStats;
        std::vector<double> emptySample = nr::ProbabilitySampling::simple_random(emptyStats.begin(), emptyStats.end(), sampleSize);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] Simple random sampling successfully!\n";
    }
}

void ProbabilitySampling_Systematic_tests()
{
    ProbabilitySampling_ContainerSystematic_test();
    ProbabilitySampling_IteratorSystematic_test();
}

void ProbabilitySampling_ContainerSystematic_test()
{
    {
        nr::NumericSample<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::ProbabilitySampling::systematic(stats, sample);

        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
        assert(sampleResult.size() == static_cast<double>(std::ceil(step)));

        nr::NumericSample<double> emptyStats;
        auto emptySample = nr::ProbabilitySampling::systematic(emptyStats, sample);
        assert(emptySample.size() == 0);
        std::cout << "[TEST] Systematic sampling successfully!\n";
    }
}

void ProbabilitySampling_IteratorSystematic_test()
{
    {
        nr::NumericSample<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::ProbabilitySampling::systematic(stats.begin(), stats.end(), sample);

        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
        assert(sampleResult.size() == static_cast<double>(std::ceil(step)));

        nr::NumericSample<double> emptyStats;
        auto emptySample = nr::ProbabilitySampling::systematic(emptyStats.begin(), emptyStats.end(), sample);
        assert(emptySample.size() == 0);
        std::cout << "[TEST] Systematic sampling successfully!\n";
    }
}

void ProbabilitySampling_Stratified_tests()
{
    ProbabilitySampling_ContainerStratified_test();
    ProbabilitySampling_IteratorStratified_test();
}

void ProbabilitySampling_ContainerStratified_test()
{
    {
        nr::NumericSample<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        std::vector<double> strat = nr::ProbabilitySampling::stratified(stats, labels, sampleSize);

        assert(strat.size() == sampleSize);

        size_t sampleSize1 = 8;
        std::vector<double> emptyStats1;
        std::vector<size_t> emptyLabels1;
        auto emptySample1 = nr::ProbabilitySampling::stratified(emptyStats1, emptyLabels1, sampleSize);
        assert(emptySample1.size() == 0);
        std::cout << "[TEST] Stratified sampling successfully!\n";
    }
}

void ProbabilitySampling_IteratorStratified_test()
{
    {
        nr::NumericSample<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        std::vector<double> strat = nr::ProbabilitySampling::stratified(stats.begin(), stats.end(), labels.begin(), sampleSize);

        assert(strat.size() == sampleSize);

        size_t sampleSize1 = 8;
        std::vector<double> emptyStats1;
        std::vector<size_t> emptyLabels1;
        auto emptySample1 = nr::ProbabilitySampling::stratified(emptyStats1.begin(), emptyStats1.end(), emptyLabels1.begin(), sampleSize);
        assert(emptySample1.size() == 0);
        std::cout << "[TEST] Stratified sampling successfully!\n";
    }
}
