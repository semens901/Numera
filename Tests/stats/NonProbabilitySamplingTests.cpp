#include "NonProbabilitySamplingTests.h"

void non_probability_sampling_tests()
{
    NonProbabilitySampling_QuotaSampling_tests();
    
    NonProbabilitySampling_HaphazardSampling_tests();

    NonProbabilitySampling_ConvenienceSampling_tests();
}

void NonProbabilitySampling_QuotaSampling_tests()
{
    NonProbabilitySampling_ContainerQuotaSampling_test();
    NonProbabilitySampling_IteratorQuotaSampling_test();
}

void NonProbabilitySampling_ContainerQuotaSampling_test()
{
    {

        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});
        // Group tags: 0, 1, 2, 3
        std::vector<size_t> labels = {1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 3, 3, 3};

        // --- Quotas for groups ---
        std::unordered_map<size_t, size_t> quotas = {
            {0, 2},  // we take 2 elements from group 0
            {1, 2},  // we take 2 elements from group 1
            {2, 1},  // we take 1 element from group 2
            {3, 3}   // we take 3 elements from group 3
        };

        auto sample = nr::NonProbabilitySampling::quotaSample(data, labels, quotas);

        // Checking the sample size
        assert(sample.size() == 8); // 2+2+1+3 = 8

        // We check that the elements are indeed from the original groups
        for (auto v : sample) {
            bool inGroup0 = std::find(data.begin() + 4, data.begin() + 9, v) != data.begin() + 9;
            bool inGroup1 = std::find(data.begin(), data.begin() + 4, v) != data.begin() + 4;
            bool inGroup2 = std::find(data.begin() + 9, data.begin() + 12, v) != data.begin() + 12;
            bool inGroup3 = std::find(data.begin() + 12, data.end(), v) != data.end();
            assert(inGroup0 || inGroup1 || inGroup2 || inGroup3);
        }

        // --- Test 2: Empty NumericSample ---
        nr::NumericSample<double> emptyData;
        std::vector<size_t> emptyLabels;
        std::unordered_map<size_t, size_t> emptyQuotas = { {0, 1} };
        auto emptySample = nr::NonProbabilitySampling::quotaSample(emptyData, emptyLabels, emptyQuotas);
        assert(emptySample.size() == 0);
    }
    std::cout << "[TEST] Quota Sampling successfully!\n";
}

void NonProbabilitySampling_IteratorQuotaSampling_test()
{
    {

        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});
        // Group tags: 0, 1, 2, 3
        std::vector<size_t> labels = {1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 3, 3, 3};

        // --- Quotas for groups ---
        std::unordered_map<size_t, size_t> quotas = {
            {0, 2},  // we take 2 elements from group 0
            {1, 2},  // we take 2 elements from group 1
            {2, 1},  // we take 1 element from group 2
            {3, 3}   // we take 3 elements from group 3
        };

        auto sample = nr::NonProbabilitySampling::quotaSample(data.begin(), data.end(), labels.begin(), quotas);

        // Checking the sample size
        assert(sample.size() == 8); // 2+2+1+3 = 8

        // We check that the elements are indeed from the original groups
        for (auto v : sample) {
            bool inGroup0 = std::find(data.begin() + 4, data.begin() + 9, v) != data.begin() + 9;
            bool inGroup1 = std::find(data.begin(), data.begin() + 4, v) != data.begin() + 4;
            bool inGroup2 = std::find(data.begin() + 9, data.begin() + 12, v) != data.begin() + 12;
            bool inGroup3 = std::find(data.begin() + 12, data.end(), v) != data.end();
            assert(inGroup0 || inGroup1 || inGroup2 || inGroup3);
        }

        // --- Test 2: Empty NumericSample ---
        nr::NumericSample<double> emptyData;
        std::vector<size_t> emptyLabels;
        std::unordered_map<size_t, size_t> emptyQuotas = { {0, 1} };
        auto emptySample = nr::NonProbabilitySampling::quotaSample(emptyData.begin(), emptyData.end(), emptyLabels.begin(), emptyQuotas);
        assert(emptySample.size() == 0);
    }
    std::cout << "[TEST] Quota Sampling successfully!\n";
}

void NonProbabilitySampling_HaphazardSampling_tests()
{
    NonProbabilitySampling_ContainerHaphazardSampling_test();
    NonProbabilitySampling_IteratorHaphazardSampling_test();
}

void NonProbabilitySampling_ContainerHaphazardSampling_test()
{
    {
        // --- Data preparation ---
        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});

        // --- Test 1: Normal sampling ---
        size_t sampleSize = 5;
        auto sample = nr::NonProbabilitySampling::haphazardSample(data, sampleSize);
        std::cout << "SAMPLE SIZE:\t" << sample.size() << std::endl;
        assert(sample.size() == sampleSize);

        // --- Test 2: sampleSize greater than the total number of elements ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::haphazardSample(data, largeSampleSize);

        assert(largeSample.size() == data.size()); // only 18 elements

        // --- Test 3: empty NumericSample ---
        nr::NumericSample<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::haphazardSample(emptyData, 5);
        assert(emptySample.size() == 0);
    }
    std::cout << "[TEST] Haphazard Sampling successfully!\n";
}

void NonProbabilitySampling_IteratorHaphazardSampling_test()
{
    {
        // --- Data preparation ---
        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});

        // --- Test 1: Normal sampling ---
        size_t sampleSize = 5;
        auto sample = nr::NonProbabilitySampling::haphazardSample(data.begin(), data.end(), sampleSize);
        std::cout << "SAMPLE SIZE:\t" << sample.size() << std::endl;
        assert(sample.size() == sampleSize);

        // --- Test 2: sampleSize greater than the total number of elements ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::haphazardSample(data.begin(), data.end(), largeSampleSize);

        assert(largeSample.size() == data.size()); // only 18 elements

        // --- Test 3: empty NumericSample ---
        nr::NumericSample<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::haphazardSample(emptyData.begin(), emptyData.end(), 5);
        assert(emptySample.size() == 0);
    }
    std::cout << "[TEST] Haphazard Sampling successfully!\n";
}

void NonProbabilitySampling_ConvenienceSampling_tests()
{
    NonProbabilitySampling_ContainerConvenienceSampling_test();
    NonProbabilitySampling_IteratorConvenienceSampling_test();
}

void NonProbabilitySampling_ContainerConvenienceSampling_test()
{
    {
        // --- Data preparation ---
        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30});

        // --- Test 1: Normal sampling ---
        size_t sampleSize = 5;
        auto sample = nr::NonProbabilitySampling::convenienceSample(data, sampleSize);

        assert(sample.size() == sampleSize);
        for (size_t i = 0; i < sampleSize; ++i)
            assert(sample[i] == data[i]); // the first elements must be taken

        // --- Test 2: sampleSize is greater than the total number of elements ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::convenienceSample(data, largeSampleSize);

        assert(largeSample.size() == data.size());
        for (size_t i = 0; i < data.size(); ++i)
            assert(largeSample[i] == data[i]);

        // --- Тест 3: пустой NumericSample ---
        nr::NumericSample<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::convenienceSample(emptyData, 5);
        assert(emptySample.size() == 0);
    }
    std::cout << "[TEST] Convenience Sampling successfully!\n";
}

void NonProbabilitySampling_IteratorConvenienceSampling_test()
{
    {
        // --- Data preparation ---
        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30});

        // --- Test 1: Normal sampling ---
        size_t sampleSize = 5;
        auto sample = nr::NonProbabilitySampling::convenienceSample(data.begin(), data.end(), sampleSize);

        assert(sample.size() == sampleSize);
        for (size_t i = 0; i < sampleSize; ++i)
            assert(sample[i] == data[i]); // the first elements must be taken

        // --- Test 2: sampleSize is greater than the total number of elements ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::convenienceSample(data.begin(), data.end(), largeSampleSize);

        assert(largeSample.size() == data.size());
        for (size_t i = 0; i < data.size(); ++i)
            assert(largeSample[i] == data[i]);

        // --- Тест 3: пустой NumericSample ---
        nr::NumericSample<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::convenienceSample(emptyData.begin(), emptyData.end(), 5);
        assert(emptySample.size() == 0);
    }
    std::cout << "[TEST] Convenience Sampling successfully!\n";
}