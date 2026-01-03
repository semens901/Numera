#include "NonProbabilitySamplingTests.h"

void non_probability_sampling_tests()
{
    {
        std::cout << "[TEST] Quota sampling with NumericSample\n";

        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});
        // Group tags: 0, 1, 2, 3
        std::vector<size_t> labels = {1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 3, 3, 3};

        // --- Квоты для групп ---
        std::unordered_map<size_t, size_t> quotas = {
            {0, 2},  // we take 2 elements from group 0
            {1, 2},  // we take 2 elements from group 1
            {2, 1},  // we take 1 element from group 2
            {3, 3}   // we take 3 elements from group 3
        };

        auto sample = nr::NonProbabilitySampling::quotaSample(data, labels, quotas);

        // Checking the sample size
        assert(sample.size() == 8); // 2+2+1+3 = 8

        // Проверяем, что элементы действительно из исходных групп
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

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Haphazard sampling with NumericSample\n";

        // --- Подготовка данных ---
        nr::NumericSample<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});

        // --- Тест 1: обычная выборка ---
        size_t sampleSize = 5;
        auto sample = nr::NonProbabilitySampling::haphazardSample(data, sampleSize);
        std::cout << "SAMPLEEEEEEE SIIIZEEEE:\t" << sample.size() << std::endl;
        assert(sample.size() == sampleSize);

        // --- Тест 2: sampleSize больше общего количества элементов ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::haphazardSample(data, largeSampleSize);

        assert(largeSample.size() == data.size()); // всего 18 элементов

        // --- Тест 3: пустой NumericSample ---
        nr::NumericSample<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::haphazardSample(emptyData, 5);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Convenience sampling with NumericSample\n";

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

        std::cout << "[TEST] successfully!\n";
    }
}
