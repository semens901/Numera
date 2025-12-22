#include "NonProbabilitySamplingTests.h"

void non_probability_sampling_tests()
{
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
        nr::CSVData<std::string, double> cv;
        cv["A"] = {1, 2, 3, 1, 4, 5};
        cv["B"] = {10, 20, 30, 40};
        cv["C"] = {100, 200};

        std::unordered_map<std::string, size_t> quotas = {
            {"A", 4},
            {"B", 3},
            {"C", 1}
        };

        auto quotaSample = nr::NonProbabilitySampling::quotaSample(cv, quotas);

        // Checking the total sample size
        assert(quotaSample.size() == 8);
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

        // Проверяем, что элементы реально из исходных групп
        for (auto v : haphazard) {
            bool inA = std::find(cv["A"].begin(), cv["A"].end(), v) != cv["A"].end();
            bool inB = std::find(cv["B"].begin(), cv["B"].end(), v) != cv["B"].end();
            bool inC = std::find(cv["C"].begin(), cv["C"].end(), v) != cv["C"].end();
            assert(inA || inB || inC);
        }

        // --- Тест 2: sampleSize больше общего количества элементов ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::haphazardSample(cv, largeSampleSize);

        assert(largeSample.size() == 9); // всего 9 элементов в cv
        for (auto v : largeSample) {
            bool inA = std::find(cv["A"].begin(), cv["A"].end(), v) != cv["A"].end();
            bool inB = std::find(cv["B"].begin(), cv["B"].end(), v) != cv["B"].end();
            bool inC = std::find(cv["C"].begin(), cv["C"].end(), v) != cv["C"].end();
            assert(inA || inB || inC);
        }

        // --- Тест 3: пустой CSVData ---
        nr::CSVData<std::string, double> emptyCv;
        auto emptySample = nr::NonProbabilitySampling::haphazardSample(emptyCv, 5);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";

    }

    {
        std::cout << "[TEST] Convenience sampling (CSVData)\n";

        nr::CSVData<std::string, double> cv;
        cv["A"] = {1, 2, 3};
        cv["B"] = {10, 20, 30, 40};
        cv["C"] = {100, 200};

        // --- Test 1: Normal sampling ---
        size_t sampleSize = 5;
        auto convenience = nr::NonProbabilitySampling::convenienceSample(cv, sampleSize);

        assert(convenience.size() == sampleSize);

        // We check that the elements are actually from the original groups
        for (auto v : convenience) {
            bool inA = std::find(cv["A"].begin(), cv["A"].end(), v) != cv["A"].end();
            bool inB = std::find(cv["B"].begin(), cv["B"].end(), v) != cv["B"].end();
            bool inC = std::find(cv["C"].begin(), cv["C"].end(), v) != cv["C"].end();
            assert(inA || inB || inC);
        }

        // --- Test 2: sampleSize is greater than the total number of elements ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::convenienceSample(cv, largeSampleSize);

        assert(largeSample.size() == 9); // всего 9 элементов в cv
        for (auto v : largeSample) {
            bool inA = std::find(cv["A"].begin(), cv["A"].end(), v) != cv["A"].end();
            bool inB = std::find(cv["B"].begin(), cv["B"].end(), v) != cv["B"].end();
            bool inC = std::find(cv["C"].begin(), cv["C"].end(), v) != cv["C"].end();
            assert(inA || inB || inC);
        }

        // --- Test 3: Empty CSVData ---
        nr::CSVData<std::string, double> emptyCv;
        auto emptySample = nr::NonProbabilitySampling::convenienceSample(emptyCv, 5);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Quota sampling with VectorData\n";

        nr::VectorData<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});
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

        // --- Test 2: Empty VectorData ---
        nr::VectorData<double> emptyData;
        std::vector<size_t> emptyLabels;
        std::unordered_map<size_t, size_t> emptyQuotas = { {0, 1} };
        auto emptySample = nr::NonProbabilitySampling::quotaSample(emptyData, emptyLabels, emptyQuotas);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Haphazard sampling with VectorData\n";

        // --- Подготовка данных ---
        nr::VectorData<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 40, 41, 42, 43, 44, 45});

        // --- Тест 1: обычная выборка ---
        size_t sampleSize = 5;
        auto sample = nr::NonProbabilitySampling::haphazardSample(data, sampleSize);

        assert(sample.size() == sampleSize);

        // --- Тест 2: sampleSize больше общего количества элементов ---
        size_t largeSampleSize = 20;
        auto largeSample = nr::NonProbabilitySampling::haphazardSample(data, largeSampleSize);

        assert(largeSample.size() == data.size()); // всего 18 элементов

        // --- Тест 3: пустой VectorData ---
        nr::VectorData<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::haphazardSample(emptyData, 5);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Convenience sampling with VectorData\n";

        // --- Data preparation ---
        nr::VectorData<double> data({10, 11, 12, 13, 20, 21, 22, 23, 24, 30});

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

        // --- Тест 3: пустой VectorData ---
        nr::VectorData<double> emptyData;
        auto emptySample = nr::NonProbabilitySampling::convenienceSample(emptyData, 5);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";
    }
}
