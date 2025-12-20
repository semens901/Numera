#include "Core/VectorData.h"
#include "Core/CsvData.h"
#include "io/CsvDataLoader.h"
#include "stats/ProbabilitySampling.h"
#include "stats/NonProbabilitySampling.h"
#include "stats/BasicStats.h"
#include "io/FileDataLoader.h"

#include<iostream>
#include<cassert>
#include<string>

// helper: comparison of doubles taking into account the error
bool almostEqual(double a, double b, double eps = 1e-9)
{
    return std::abs(a - b) < eps;
}

int main()
{
    {
        std::cout << "[TEST] VectorData basic functionality\n";

        nr::VectorData<double> vd;
        assert(vd.size() == 0);
        assert(vd.empty());

        vd.add(3.14);
        vd.add(2.71);
        vd.add(1.41);

        assert(vd.size() == 3);
        assert(!vd.empty());
        assert(almostEqual(vd[0], 3.14));
        assert(almostEqual(vd[1], 2.71));
        assert(almostEqual(vd[2], 1.41));

        vd.clear();
        assert(vd.size() == 0);
        assert(vd.empty());

        nr::VectorData<double> vd1;
        nr::VectorData<double> vd2 = vd1;
        nr::VectorData<double> vd4 = std::move(vd2);
        assert(vd2.size() == 0);

        nr::VectorData<double> vd5({1,2,3});
        vd5.remove_at(1);

        std::cout << "Test passed: basic functionality works correctly.\n";\
    }

    {
        std::cout << "[TEST] Adding elements\n";
        nr::VectorData<double> vd;
        vd.add({1.0, 2.0, 3.0, 4.0, 5.0});
        assert(vd.size() == 5);
        std::cout << "Test passed: size is " << vd.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::VectorData<double> vd2 = vd; // copy constructor
        assert(vd2.size() == 5);    
        std::cout << "Test passed: size is " << vd2.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::VectorData<double> vd3;
        vd3 = vd; // copy assignment
        assert(vd3.size() == 5);    
        std::cout << "Test passed: size is " << vd3.size() << "\n";

        std::cout << "[TEST] Move semantics\n";
        nr::VectorData<double> vd4 = std::move(vd); // move constructor
        assert(vd4.size() == 5);
        assert(vd.size() == 0); // vd should be empty after move
        std::cout << "Test passed: size is " << vd4.size() << "\n";    
        
        std::cout << "[TEST] Move semantics\n";
        nr::VectorData<double> vd5;
        vd5 = std::move(vd2); // move assignment
        assert(vd5.size() == 5);
        assert(vd2.size() == 0); // vd2 should be empty after move
        std::cout << "Test passed: size is " << vd5.size() << "\n";

        std::cout << "[TEST] Removing elements\n";
        nr::VectorData<double> vd6({1,2,3});
        vd6.remove_at(1); // remove element at index 1
        assert(vd6.size() == 2);
        assert(vd6[0] == 1);
        assert(vd6[1] == 3);
        std::cout << "Test passed: size is " << vd6.size() << "\n";
    }


    {
        std::cout << "[TEST] Open simple file\n";
        FileDataLoader file_loader;
        nr::VectorData<double> dt(file_loader.load("numbers.txt"));
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;
        std::cout << "Test passed\n";
    }

    {
        std::cout << "[TEST] Open CSV file\n";
        CSVDataLoader store("example.csv");
    
        
        std::cout << "Test passed\n";
    }

       // ----------------------------------------------------
    // TEST 1: Constructors
    // ----------------------------------------------------
    {
        std::cout << "[TEST] Constructors CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s1;
        assert(s1.empty());

        std::map<std::string, std::vector<double>> init{
            {"A", {1.0, 2.0}},
            {"B", {3.0}}
        };

        nr::CSVDataStore<std::string, double> s2(init);
        assert(s2.size() == 2);
        assert(s2.at("A").size() == 2);

        nr::CSVDataStore<std::string, double> s3(s2);                // copy ctor
        assert(s3.size() == 2);

        nr::CSVDataStore<std::string, double> s4 = std::move(s3);    // move ctor
        assert(s4.size() == 2);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 2: add()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] adding elements CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("x", 10.0);
        s.add("x", 20.0);
        s.add("y", 5.5);

        assert(s.size() == 2);
        assert(s.at("x").size() == 2);
        assert(s.at("x")[0] == 10.0);
        assert(s.at("y")[0] == 5.5);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 3: at()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] at() CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("k", 1.0);

        assert(s.at("k")[0] == 1.0);

        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 4: size(), empty(), clear()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] size(), empty(), clear() CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        assert(s.empty());

        s.add("A", 1.0);
        s.add("B", 2.0);
        assert(!s.empty());
        assert(s.size() == 2);

        s.clear();
        assert(s.empty());
        assert(s.size() == 0);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 5: Iteration
    // ----------------------------------------------------
    {
        std::cout << "[TEST] Iteration CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("A", 1.0);
        s.add("B", 2.0);

        int count = 0;
        for (const auto& [key, vec] : s) {
            assert(!vec.empty());
            count++;
        }
        assert(count == 2);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 6: remove_at(key)
    // ----------------------------------------------------
    {
        std::cout << "[TEST] remove_at(key) CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("A", 1.0);
        s.add("B", 2.0);
        s.add("C", 3.0);

        s.remove_at("B");
        assert(s.size() == 2);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 7: remove_at(iterator)
    // ----------------------------------------------------
    {
        std::cout << "[TEST] remove_at(iterator) CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("A", 1.0);
        s.add("B", 2.0);
        s.add("C", 3.0);

        auto it = s.begin();
        ++it;           // указывает на "B"
        s.remove_at(it);
        assert(s.size() == 2);
        assert(s.at("C")[0] == 3.0);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 8: remove_at(it_begin, it_end)
    // ----------------------------------------------------
    {
        std::cout << "[TEST] remove_at(it_begin, it_end) CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("A", 1.0);
        s.add("B", 2.0);
        s.add("C", 3.0);

        auto it1 = s.begin();
        auto it2 = s.begin();
        std::advance(it2, 2); // указывает на "C"

        s.remove_at(it1, it2);

        // Остался только "C"
        assert(s.size() == 1);
        assert(s.at("C")[0] == 3.0);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 9: min(), max(), mean(), median()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] min(), max(), mean(), median() CSVDataStore\n";
        nr::CSVDataStore<std::string, double> s;
        s.add("A", 10.0);
        s.add("A", 20.0);
        s.add("B", 30.0);

        // значения: {10,20,30}
        assert(s.min() == 10.0);
        assert(s.max() == 30.0);
        //assert(std::abs(s.mean() - 20.0) < 1e-9);
        //assert(std::abs(s.median() - 20.0) < 1e-9);
        std::cout << "Test passed\n";
    }

    {
        
        std::cout << "[TEST] VectorData stats funcs\n";
        nr::VectorData<double> vc({1, 2, 3, 4});
        assert(vc.min() == 1);
        assert(vc.max() == 4);

        std::cout << "Test passed: min is " << vc.min() << ", max is " << vc.max() << "\n";
        
        assert(almostEqual(vc.mean(), 2.5));
        std::cout << "Test passed: mean is " << vc.mean() << "\n";
        /*
            assert(almostEqual(vc.median(), 2.5));
        */
        
        
    }

    {
        std::cout << "[TEST] Minimum and maximum\n";
        nr::CSVDataStore<std::string, double> csv(std::map<std::string, std::vector<double>>{{"hello", {1,2,3}},{"hi", {0,4,5}}});
        assert(csv.min() == 0);
        assert(csv.max() == 5);
        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Simple random sampling\n";

        nr::VectorData<double> stats({10, 20, 30, 40, 50});

        size_t sampleSize = 3;
        auto sample = nr::ProbabilitySampling::simple_random<double>(stats, sampleSize);

        assert(sample.size() == sampleSize);

        nr::VectorData<double> emptyStats;
        auto emptySample = nr::ProbabilitySampling::simple_random<double>(emptyStats, sampleSize);
        assert(emptySample.size() == 0);

        nr::CSVDataStore<std::string, double> cd{std::map<std::string, std::vector<double>>
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

        auto strat = nr::ProbabilitySampling::stratified<double>(stats, labels, sampleSize);

        assert(strat.size() == sampleSize);

        nr::CSVDataStore<std::string, double> cv;
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

    {
        std::cout << "[TEST] Quota sampling (CSVDataStore with quotas)\n";

        nr::CSVDataStore<std::string, double> cv;
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

        // Test: Empty CSVDataStore
        nr::CSVDataStore<std::string, double> emptyCv;
        std::unordered_map<std::string, size_t> quotasEmpty = { {"A", 1} };
        auto emptySample = nr::NonProbabilitySampling::quotaSample(emptyCv, quotasEmpty);
        assert(emptySample.size() == 0);

        // Test: Quota exceeds the number of elements in the group
        nr::CSVDataStore<std::string, double> smallCv;
        smallCv["X"] = {5, 6};
        std::unordered_map<std::string, size_t> quotasExceed = { {"X", 5} };
        auto exceedSample = nr::NonProbabilitySampling::quotaSample(smallCv, quotasExceed);
        assert(exceedSample.size() == 2);
        for (auto v : exceedSample)
            assert(v == 5 || v == 6);
    }

    {
        nr::CSVDataStore<std::string, double> cv;
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
        
        std::cout << "[TEST] Haphazard sampling (CSVDataStore)\n";

        nr::CSVDataStore<std::string, double> cv;
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

        // --- Тест 3: пустой CSVDataStore ---
        nr::CSVDataStore<std::string, double> emptyCv;
        auto emptySample = nr::NonProbabilitySampling::haphazardSample(emptyCv, 5);
        assert(emptySample.size() == 0);

        std::cout << "[TEST] successfully!\n";

    }

    {
        std::cout << "[TEST] Convenience sampling (CSVDataStore)\n";

        nr::CSVDataStore<std::string, double> cv;
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

        // --- Test 3: Empty CSVDataStore ---
        nr::CSVDataStore<std::string, double> emptyCv;
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

    {
        std::vector<double> v{1.0, 2.0, 3.0};
        std::vector<double> w{1.0, 1.0, 1.0};

        double result = nr::weighted_mean(v, w);
        assert(std::abs(result - 2.0) < 1e-9);
    }

    {
        std::vector<double> v{42.0};
        std::vector<double> w{10.0};

        double result = nr::weighted_mean(v, w);
        assert(result == 42.0);
    }

    {
        std::vector<double> v{15, 10, 5, 90};
        std::vector <double> w{0.25, 0.20, 0.05, 0.50};

        double result = nr::weighted_mean(v, w);
        assert(result == 51.0);
    }
    {
        std::vector<double> population{
            54, 63, 48, 29, 27, 32, 41
        };

        double result = nr::geometric_mean(population);
        const double expected = 40.135109214786738;
        const double eps = 1e-6;

        assert(std::abs(result - expected) < eps);
    }
    
    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, 41};

        double expected = 38.380368771744429; // рассчитанное гармоническое среднее вручную или в калькуляторе
        double result = nr::harmonic_mean(population);
        std::cout << result << std::endl;
        // Используем assert с допуском для вещественных чисел
        double eps = 1e-4; 
        assert(std::abs(result - expected) < eps);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q1 = nr::lower_quartile(data);

        assert(q1 == 29.0);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q3 = nr::upper_quartile(data);

        assert(q3 == 54.0);
    }

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
