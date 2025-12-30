#include "BasicStatsTests.h"

bool is_close(double a, double b, double epsilon = 0.0001) {
    return std::abs(a - b) < epsilon;
}

void basic_stats_tests()
{
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
        nr::VectorData<double> v({15, 10, 5, 90});
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
        std::vector<double> data1 = {1.0, 3.0, 9.0};
        double gm1 = nr::geometric_mean(data1.begin(), data1.end());
        assert(std::abs(gm1 - 3.0) < 1e-9); // geometric arithmetic_mean = 3

        std::vector<int> data2 = {42};
        int gm2 = nr::geometric_mean(data2.begin(), data2.end());
        assert(gm2 == 42);

        std::vector<int> data3;
        bool exception_thrown = false;
        try {
            nr::geometric_mean(data3.begin(), data3.end());
        } catch (const std::invalid_argument&) {
            exception_thrown = true;
        }
        assert(exception_thrown);

        std::vector<double> data4 = {1.0, -2.0, 3.0};
        exception_thrown = false;
        try {
            nr::geometric_mean(data4.begin(), data4.end());
        } catch (const std::domain_error&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }
    
    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, 41};

        double expected = 38.380368771744429; // calculated harmonic arithmetic_mean manually or using a calculator
        double result = nr::harmonic_mean(population);
        std::cout << result << std::endl;
        // Using assert with tolerance for real numbers
        double eps = 1e-4; 
        assert(std::abs(result - expected) < eps);
    }

    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, 41};

        double expected = 38.380368771744429; // calculated harmonic arithmetic_mean manually or using a calculator
        double result = nr::harmonic_mean(population.begin(), population.end());
        std::cout << result << std::endl;
        // Using assert with tolerance for real numbers
        double eps = 1e-4; 
        assert(std::abs(result - expected) < eps);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q1 = nr::lower_quartile(data);

        assert(q1 == 29.0);
    }
    
    {
        nr::VectorData<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q1 = nr::lower_quartile(data.begin(), data.end());

        assert(q1 == 29.0);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q3 = nr::upper_quartile(data);

        assert(q3 == 54.0);
    }

    {
        nr::VectorData<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q3 = nr::upper_quartile(data.begin(), data.end());

        assert(q3 == 54.0);
    }

    {
        std::vector<int> data{5, 3, 8, 1, 4};

        int result = nr::min(data.begin(), data.end());

        assert(result == 1);
    }

    {
        // 1. Common case: different values
        std::map<int, std::vector<int>> m1 = {
            {1, {10, 5, 8}},
            {2, {20, 3, 15}},
            {3, {7, 42}}
        };
        assert(nr::min(m1) == 3);

        // 2. The case with negative numbers
        std::map<std::string, std::vector<double>> m2 = {
            {"a", {1.5, -2.5, 0.0}},
            {"b", {-10.2, 5.5}}
        };
        assert(nr::min(m2) == -10.2);

        // 3. Mixed case: there are empty vectors inside the map
        std::map<int, std::vector<int>> m3 = {
            {1, {}},
            {2, {100, 50}},
            {3, {}}
        };
        assert(nr::min(m3) == 50);

        // 4. Checking for an empty map exception
        std::map<int, std::vector<int>> empty_map;
        try {
            nr::min(empty_map);
            assert(false);
        } catch (const std::invalid_argument& e) {
            assert(std::string(e.what()) == "min: empty map");
        }
    }

    {
        // 1. Common case: different values
        nr::CSVData<int, int> m1 = {
            {1, {10, 5, 8}},
            {2, {20, 3, 15}},
            {3, {7, 42}}
        };
        assert(nr::min(m1) == 3);

        // 2. The case with negative numbers
        std::map<std::string, std::vector<double>> m2 = {
            {"a", {1.5, -2.5, 0.0}},
            {"b", {-10.2, 5.5}}
        };
        assert(nr::min(m2) == -10.2);

        // 3. Mixed case: there are empty vectors inside the map
        nr::CSVData<int, int> m3 = {
            {1, {}},
            {2, {100, 50}},
            {3, {}}
        };
        assert(nr::min(m3) == 50);

        // 4. Checking for an empty map exception
        nr::CSVData<int, int> empty_map;
        try {
            nr::min(empty_map);
            assert(false);
        } catch (const std::invalid_argument& e) {
            assert(std::string(e.what()) == "min: empty CSVData");
        }
    }

    {
        std::vector<int> data{5, 3, 8, 1, 4};

        int result = nr::max(data.begin(), data.end());

        assert(result == 8);
    }

    {
        // 1. Standard Test: Different Groups of Numbers
        std::map<std::string, std::vector<int>> m1 = {
            {"group1", {1, 5, 3}},
            {"group2", {10, 2, 8}},
            {"group3", {4, 9}}
        };
        assert(nr::max(m1) == 10);

        // 2. Negative numbers test
        std::map<int, std::vector<double>> m2 = {
            {100, {-10.5, -20.0}},
            {200, {-5.2, -1.1}}
        };
        assert(nr::max(m2) == -1.1);

        // 3. Gap test (empty vectors inside)
        std::map<int, std::vector<int>> m3 = {
            {1, {}},
            {2, {42}},
            {3, {}}
        };
        assert(nr::max(m3) == 42);

        // 4. Test for exception on empty map
        std::map<int, std::vector<int>> m_empty;
        bool exception_thrown = false;
        try {
            nr::max(m_empty);
        } catch (const std::invalid_argument& e) {
            exception_thrown = true;
            assert(std::string(e.what()) == "max: empty container");
        }
        assert(exception_thrown);

        // 5. Test with the same values
        std::map<char, std::vector<int>> m4 = {
            {'a', {7, 7}},
            {'b', {7}}
        };
        assert(nr::max(m4) == 7);
    }

    {
        // 1. Standard Test: Different Groups of Numbers
        nr::CSVData<std::string, int> m1 = {
            {"group1", {1, 5, 3}},
            {"group2", {10, 2, 8}},
            {"group3", {4, 9}}
        };
        assert(nr::max(m1) == 10);

        // 2. Negative numbers test
        nr::CSVData<int, double> m2 = {
            {100, {-10.5, -20.0}},
            {200, {-5.2, -1.1}}
        };
        assert(nr::max(m2) == -1.1);

        // 3. Gap test (empty vectors inside)
        nr::CSVData<int, int> m3 = {
            {1, {}},
            {2, {42}},
            {3, {}}
        };
        assert(nr::max(m3) == 42);

        // 4. Test for exception on empty map
        nr::CSVData<int, double> m_empty;
        bool exception_thrown = false;
        try {
            nr::max(m_empty);
        } catch (const std::invalid_argument& e) {
            exception_thrown = true;
            assert(std::string(e.what()) == "max: empty container");
        }
        assert(exception_thrown);

        // 5. Test with the same values
        nr::CSVData<char, int> m4 = {
            {'a', {7, 7}},
            {'b', {7}}
        };
        assert(nr::max(m4) == 7);
    }

    {
        std::vector<double> data1 = {1.0, 2.0, 3.0, 4.0};
        double mean1 = nr::arithmetic_mean(data1.begin(), data1.end(), 0.0);
        assert(mean1 == 2.5); // (1+2+3+4)/4 = 2.5

        std::vector<int> data2 = {10};
        int mean2 = nr::arithmetic_mean(data2.begin(), data2.end(), 0);
        assert(mean2 == 10);

        std::vector<int> data3;
        bool exception_thrown = false;
        try {
            nr::arithmetic_mean(data3.begin(), data3.end(), 0);
        } catch (const std::invalid_argument&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }
    
    {
        // Test 1: Simple integer-based mean
        // Calculation: (10 + 20 + 30) / 3 keys = 60 / 3 = 20
        std::map<int, std::vector<double>> m1 = {
            {1, {10.0}},
            {2, {20.0}},
            {3, {30.0}}
        };
        assert(std::abs(nr::arithmetic_mean(m1) - 20.0) < 1e-9);

        // Test 2: Multiple elements per key
        // Calculation: (1 + 2 + 3 + 4) / 2 keys = 10 / 2 = 5.0
        std::map<std::string, std::vector<double>> m2 = {
            {"A", {1.0, 2.0}},
            {"B", {3.0, 4.0}}
        };
        assert(std::abs(nr::arithmetic_mean(m2) - 5.0) < 1e-9);

        // Test 3: Handling empty map (Exception test)
        std::map<int, std::vector<double>> empty_map;
        bool exception_caught = false;
        try {
            nr::arithmetic_mean(empty_map);
        } catch (const std::invalid_argument& e) {
            exception_caught = true;
        }
        assert(exception_caught);
    }

    {
        // Test 1: Simple integer-based mean
        // Calculation: (10 + 20 + 30) / 3 keys = 60 / 3 = 20
        nr::CSVData<int, double> m1 = {
            {1, {10.0}},
            {2, {20.0}},
            {3, {30.0}}
        };
        assert(std::abs(nr::arithmetic_mean(m1) - 20.0) < 1e-9);

        // Test 2: Multiple elements per key
        // Calculation: (1 + 2 + 3 + 4) / 2 keys = 10 / 2 = 5.0
        nr::CSVData<std::string, double> m2 = {
            {"A", {1.0, 2.0}},
            {"B", {3.0, 4.0}}
        };
        assert(std::abs(nr::arithmetic_mean(m2) - 5.0) < 1e-9);

        // Test 3: Handling empty map (Exception test)
        nr::CSVData<int, double> empty_map;
        bool exception_caught = false;
        try {
            nr::arithmetic_mean(empty_map);
        } catch (const std::invalid_argument& e) {
            exception_caught = true;
        }
        assert(exception_caught);
    }

    {
        std::vector<double> data1 = {3.0, 1.0, 4.0, 2.0, 5.0};
        double med1 = nr::median(data1.begin(), data1.end());
        assert(med1 == 3.0);

        std::vector<int> data2 = {10, 20, 30, 40};
        int med2 = nr::median(data2.begin(), data2.end());
        assert(med2 == 25); // (20+30)/2

        std::vector<int> data3 = {42};
        int med3 = nr::median(data3.begin(), data3.end());
        assert(med3 == 42);

        std::vector<int> data4;
        bool exception_thrown = false;
        try {
            nr::median(data4.begin(), data4.end());
        } catch (const std::invalid_argument&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }

    {
        // 1. Test Odd number of total elements
        // Sorted: {1, 3, 5, 7, 9} -> Middle is 5
        std::map<int, std::vector<double>> m1 = {
            {1, {3.0, 1.0}},
            {2, {7.0, 5.0, 9.0}}
        };
        assert(std::abs(nr::median(m1) - 5.0) < 1e-9);

        // 2. Test Even number of total elements
        // Sorted: {1, 2, 3, 4} -> Average of 2 and 3 is 2.5
        std::map<std::string, std::vector<double>> m2 = {
            {"first", {4.0, 1.0}},
            {"second", {3.0, 2.0}}
        };
        assert(std::abs(nr::median(m2) - 2.5) < 1e-9);

        // 3. Test with single element
        std::map<int, std::vector<int>> m3 = {{1, {42}}};
        assert(nr::median(m3) == 42);

        // 4. Test Exception for empty map
        std::map<int, std::vector<int>> empty_map;
        bool caught = false;
        try {
            nr::median(empty_map);
        } catch (const std::invalid_argument& e) {
            caught = true;
        }
        assert(caught);

        std::cout << "All median tests passed successfully!" << std::endl;
    }

    {
        // 1. Test Odd number of total elements
        // Sorted: {1, 3, 5, 7, 9} -> Middle is 5
        nr::CSVData<int, double> m1 = {
            {1, {3.0, 1.0}},
            {2, {7.0, 5.0, 9.0}}
        };
        assert(std::abs(nr::median(m1) - 5.0) < 1e-9);

        // 2. Test Even number of total elements
        // Sorted: {1, 2, 3, 4} -> Average of 2 and 3 is 2.5
        nr::CSVData<std::string, double> m2 = {
            {"first", {4.0, 1.0}},
            {"second", {3.0, 2.0}}
        };
        assert(std::abs(nr::median(m2) - 2.5) < 1e-9);

        // 3. Test with single element
        nr::CSVData<int, int> m3 = {{1, {42}}};
        assert(nr::median(m3) == 42);

        // 4. Test Exception for empty map
        nr::CSVData<int, int> empty_map;
        bool caught = false;
        try {
            nr::median(empty_map);
        } catch (const std::invalid_argument& e) {
            caught = true;
        }
        assert(caught);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        // Sorted data:
        // [27, 29, 32, 41, 48, 54, 63]

        double p25 = nr::percentile(data, 25);
        double p50 = nr::percentile(data, 50);
        double p75 = nr::percentile(data, 75);

        assert(std::abs(p25 - 30.5) < 1e-9);
        assert(std::abs(p50 - 41.0) < 1e-9);
        assert(std::abs(p75 - 51.0) < 1e-9);
    }

    {
        std::vector<int> data;
        data.reserve(100);

        for (int i = 100; i >= 1; --i)
            data.push_back(i);

        double p50 = nr::percentile(data, 50);

        assert(std::abs(p50 - 50.5) < 1e-9);
    }

    {
        std::vector<int> data;
        data.reserve(100);

        for (int i = 100; i >= 1; --i)
            data.push_back(i);

        double p50 = nr::percentile(data, 50);

        assert(std::abs(p50 - 50.5) < 1e-9);
    }

    {
        std::vector<double> data(100, 42.0);
        assert(nr::percentile(data, 10) == 42.0);
        assert(nr::percentile(data, 50) == 42.0);
        assert(nr::percentile(data, 90) == 42.0);
    }

    {
        std::vector<int> data{1, 2, 2, 3, 4};

        auto m = nr::mode(data);
        assert(m.has_value());
        assert(*m == 2);

        auto ms = nr::modes(data);
        assert(ms.size() == 1);
        assert(ms[0] == 2);
    }

    {
        std::vector<int> data{1, 2, 3, 4, 5};

        auto m = nr::mode(data);
        assert(!m.has_value());

        auto ms = nr::modes(data);
        assert(ms.empty());
    }
    {
        std::vector<int> data{1, 1, 2, 2, 3};

        auto m = nr::mode(data);
        assert(!m.has_value());

        auto ms = nr::modes(data);
        assert(ms.size() == 2);

        std::sort(ms.begin(), ms.end());
        assert(ms[0] == 1);
        assert(ms[1] == 2);
    }

    {
        std::vector<int> data{1, 1, 2, 2, 3, 3};

        auto m = nr::mode(data);
        assert(!m.has_value());

        auto ms = nr::modes(data);
        assert(ms.size() == 3);

        std::sort(ms.begin(), ms.end());
        assert((ms == std::vector<int>{1, 2, 3}));
    }

    {
        std::vector<int> data{42};

        auto m = nr::mode(data);
        assert(!m.has_value()); // частота = 1 → моды нет

        auto ms = nr::modes(data);
        assert(ms.empty());
    }

    {
        std::vector<int> data;

        auto m = nr::mode(data);
        assert(!m.has_value());

        auto ms = nr::modes(data);
        assert(ms.empty());
    }

    {
        std::vector<int> data;

        for (int i = 0; i < 10; ++i) data.push_back(1);
        for (int i = 0; i < 20; ++i) data.push_back(2);
        for (int i = 0; i < 5; ++i)  data.push_back(3);
        for (int i = 4; i <= 69; ++i) data.push_back(i);

        auto m = nr::mode(data);
        assert(m.has_value());
        assert(*m == 2);

        auto ms = nr::modes(data);
        assert(ms.size() == 1);
        assert(ms[0] == 2);
    }

    {
        std::vector<int> data{1, 2, 3, 4, 5};

        auto result = nr::Scope(data);
        assert(result == 4); // 5 - 1
    }
    {
        std::vector<int> data{10, 3, 7, 1, 9};

        auto result = nr::Scope(data);
        assert(result == 9); // 10 - 1
    }

    {
        std::vector<int> data{-10, -5, -3, -20};

        auto result = nr::Scope(data);
        assert(result == 17); // -3 - (-20)
    }

    {
        std::vector<int> data{-5, 0, 10};

        auto result = nr::Scope(data);
        assert(result == 15); // 10 - (-5)
    }

    {
        std::vector<int> data{-5, 0, 10};

        auto result = nr::Scope(data);
        assert(result == 15); // 10 - (-5)
    }
    
    {
        std::vector<int> data;
        data.reserve(100);

        for (int i = 1; i <= 100; ++i)
            data.push_back(i);

        auto result = nr::Scope(data);
        assert(result == 99); // 100 - 1
    }

    {
        std::vector<int> data1 = {1, 2, 3, 4, 5, 6, 7, 8};
        assert(is_close(nr::interquartile_range(data1), 4.0));

        std::vector<int> data2 = {9, 1, 8, 2, 7, 3, 6, 4, 5}; // Неотсортированные
        assert(is_close(nr::interquartile_range(data2), 5.0));

        std::vector<double> data3 = {1.0, 2.0, 3.0, 4.0};
        assert(is_close(nr::interquartile_range(data3), 2.0));


        std::cout << "All interquartile_range tests passed!" << std::endl;
    }

    {
        // Тест 1: Простой набор данных
        // Данные: {2, 2, 3, 4, 14}, Mean = 5
        // Отклонения: |2-5|=3, |2-5|=3, |3-5|=2, |4-5|=1, |14-5|=9
        // Сумма отклонений: 18. MAD = 18 / 5 = 3.6
        std::vector<int> data1 = {2, 2, 3, 4, 14};
        assert(is_close(nr::mean_absolute_deviation(data1), 3.6));

        // Тест 2: Все элементы одинаковые
        // Данные: {5, 5, 5, 5}, Mean = 5
        // Отклонения все равны 0. MAD = 0
        std::vector<double> data2 = {5.0, 5.0, 5.0, 5.0};
        assert(is_close(nr::mean_absolute_deviation(data2), 0.0));

        // Тест 3: Отрицательные значения
        // Данные: {-10, 10}, Mean = 0
        // Отклонения: |-10-0|=10, |10-0|=10
        // Сумма: 20. MAD = 20 / 2 = 10.0
        std::vector<int> data3 = {-10, 10};
        assert(is_close(nr::mean_absolute_deviation(data3), 10.0));

        // Тест 4: Дробные значения
        // Данные: {1.5, 2.5, 3.5, 4.5}, Mean = 3.0
        // Отклонения: 1.5, 0.5, 0.5, 1.5. Сумма: 4.0. MAD = 4 / 4 = 1.0
        std::vector<double> data4 = {1.5, 2.5, 3.5, 4.5};
        assert(is_close(nr::mean_absolute_deviation(data4), 1.0));

        std::cout << "All mean_absolute_deviation tests passed!" << std::endl;
    }
}