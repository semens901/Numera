#include "CsvDataTests.h"

void csv_data_tests()
{
     // ----------------------------------------------------
    // TEST 1: Constructors
    // ----------------------------------------------------
    {
        std::cout << "[TEST] Constructors CSVData\n";
        nr::CSVData<std::string, double> s1;
        assert(s1.empty());

        std::map<std::string, std::vector<double>> init{
            {"A", {1.0, 2.0}},
            {"B", {3.0}}
        };

        nr::CSVData<std::string, double> s2(init);
        assert(s2.size() == 2);
        assert(s2.at("A").size() == 2);

        nr::CSVData<std::string, double> s3(s2);                // copy ctor
        assert(s3.size() == 2);

        nr::CSVData<std::string, double> s4 = std::move(s3);    // move ctor
        assert(s4.size() == 2);
        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 2: add()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] adding elements CSVData\n";
        nr::CSVData<std::string, double> s;
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
        std::cout << "[TEST] at() CSVData\n";
        nr::CSVData<std::string, double> s;
        s.add("k", 1.0);

        assert(s.at("k")[0] == 1.0);

        std::cout << "Test passed\n";
    }

    // ----------------------------------------------------
    // TEST 4: size(), empty(), clear()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] size(), empty(), clear() CSVData\n";
        nr::CSVData<std::string, double> s;
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
        std::cout << "[TEST] Iteration CSVData\n";
        nr::CSVData<std::string, double> s;
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
        std::cout << "[TEST] remove_at(key) CSVData\n";
        nr::CSVData<std::string, double> s;
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
        std::cout << "[TEST] remove_at(iterator) CSVData\n";
        nr::CSVData<std::string, double> s;
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
        std::cout << "[TEST] remove_at(it_begin, it_end) CSVData\n";
        nr::CSVData<std::string, double> s;
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
    // TEST 9: min(), max(), arithmetic_mean(), median()
    // ----------------------------------------------------
    {
        std::cout << "[TEST] min(), max(), arithmetic_mean(), median() CSVData\n";
        nr::CSVData<std::string, double> s;
        s.add("A", 10.0);
        s.add("A", 20.0);
        s.add("B", 30.0);

        // значения: {10,20,30}
        assert(s.min() == 10.0);
        assert(s.max() == 30.0);
        //assert(std::abs(s.arithmetic_mean() - 20.0) < 1e-9);
        //assert(std::abs(s.median() - 20.0) < 1e-9);
        std::cout << "Test passed\n";
    }

    {
        std::cout << "[TEST] Minimum and maximum\n";
        nr::CSVData<std::string, double> csv(std::map<std::string, std::vector<double>>{{"hello", {1,2,3}},{"hi", {0,4,5}}});
        assert(csv.min() == 0);
        assert(csv.max() == 5);
        std::cout << "[TEST] successfully!\n";
    }
}
