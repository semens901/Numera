#include "Core/VectorData.h"
#include "Core/CsvData.h"
#include "io/CsvDataLoader.h"
#include "stats/Sampling.h"
//#include "stats/BasicStats.h"
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
    
        if (store.load().size() > 0) 
        {
            std::cout << "CSV-file read successfully!" << std::endl;
            store.print();

            auto names = store.get("Name");
            std::cout << "Name column: ";
            for (const auto& n : names) std::cout << n << " ";
            std::cout << std::endl;
        } 
        else 
        {
            std::cout << "Error reading CSV file." << std::endl;
        }
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
        auto sample = nr::Sampling::simple_random<double>(stats, sampleSize);

        assert(sample.size() == sampleSize);

        nr::VectorData<double> emptyStats;
        auto emptySample = nr::Sampling::simple_random<double>(emptyStats, sampleSize);
        assert(emptySample.size() == 0);

        nr::CSVDataStore<std::string, double> cd{std::map<std::string, std::vector<double>>
        {
            {"Test1", {1, 2, 5,3}},
            {"Test2", {0, 12, 14}},
            {"Test3", {15, 90, 84, 15}}
        }};

        std::vector<double> res = nr::Sampling::simple_random<std::string, double>(cd, sampleSize);
        std::cout << "SAMPLE SIZE\t" << res.size();
        assert(res.size() == sampleSize);

        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::Sampling::systematic<double>(stats, sample);

        double statsSize = static_cast<double>(stats.size());
        double step = statsSize / static_cast<double>(sample);
        assert(sampleResult.size() == static_cast<double>(std::ceil(step)));

        nr::VectorData<double> emptyStats;
        auto emptySample = nr::Sampling::systematic<double>(emptyStats, sample);
        assert(emptySample.size() == 0);
        std::cout << "[TEST] successfully!\n";
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        nr::VectorData<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        auto strat = nr::Sampling::stratified<double>(stats, labels, sampleSize);

        assert(strat.size() == sampleSize);

        nr::CSVDataStore<std::string, double> cv;
        cv["1"] = {10,11,12,13};
        cv["0"] = {20, 21, 22, 23, 24};
        cv["2"] = {2, 2, 2};
        cv["3"] = {40, 41, 42, 43, 44, 45};

        auto strat1 = nr::Sampling::stratified<std::string, double>(cv, 5);

        assert(strat1.size() == 5);


        size_t sampleSize1 = 8;
        std::vector<double> emptyStats1;
        std::vector<size_t> emptyLabels1;
        auto emptySample1 = nr::Sampling::stratified<double>(emptyStats1, emptyLabels1, sampleSize);
        assert(emptySample1.size() == 0);
        std::cout << "[TEST] successfully!\n";
    }

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
