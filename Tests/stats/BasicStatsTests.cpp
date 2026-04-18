#include "BasicStatsTests.h"

// is_close: compare two floating-point values for approximate equality.
// Returns true when the absolute difference between `a` and `b` is
// strictly less than `epsilon`. Useful in tests to avoid relying on
// exact equality for results of floating-point computations.
bool is_close(double a, double b, double epsilon = 0.0001) {
    return std::abs(a - b) < epsilon;
}

void basic_stats_tests()
{
    std::cout << "[TESTS] Basic statistics\n";
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
        nr::NumericSample<double> v({15, 10, 5, 90});
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

        std::vector<double> data2 = {42};
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
        nr::NumericSample<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q1 = nr::lower_quartile(data.begin(), data.end());

        assert(q1 == 29.0);
    }

    {
        std::vector<int> data{54, 63, 48, 29, 27, 32, 41};

        auto q3 = nr::upper_quartile(data);

        assert(q3 == 54.0);
    }

    {
        nr::NumericSample<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q3 = nr::upper_quartile(data.begin(), data.end());

        assert(q3 == 54.0);
    }

    {
        std::vector<int> data{5, 3, 8, 1, 4};

        int result = nr::min(data.begin(), data.end());

        assert(result == 1);
    }

    {
        std::vector<int> data{5, 3, 8, 1, 4};

        int result = nr::max(data.begin(), data.end());

        assert(result == 8);
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
        // Test 1: Simple Dataset
        // Data: {2, 2, 3, 4, 14}, Mean = 5
        // Deviations: |2-5|=3, |2-5|=3, |3-5|=2, |4-5|=1, |14-5|=9
        // Sum of deviations: 18. MAD = 18 / 5 = 3.6
        std::vector<int> data1 = {2, 2, 3, 4, 14};
        assert(is_close(nr::mean_absolute_deviation(data1), 3.6));

        // Test 2: All elements are the same
        // Data: {5, 5, 5, 5}, Mean = 5
        // Deviations are all 0. MAD = 0
        std::vector<double> data2 = {5.0, 5.0, 5.0, 5.0};
        assert(is_close(nr::mean_absolute_deviation(data2), 0.0));

        // Test 3: Negative values
        // Data: {-10, 10}, Mean = 0
        // Deviations: |-10-0|=10, |10-0|=10
        // Sum of deviations: 20. MAD = 20 / 2 = 10.0
        std::vector<int> data3 = {-10, 10};
        assert(is_close(nr::mean_absolute_deviation(data3), 10.0));

        // Test 4: Fractional values
        // Data: {1.5, 2.5, 3.5, 4.5}, Mean = 3.0
        // Deviations: 1.5, 0.5, 0.5, 1.5. Sum of deviations: 4.0. MAD = 4 / 4 = 1.0
        std::vector<double> data4 = {1.5, 2.5, 3.5, 4.5};
        assert(is_close(nr::mean_absolute_deviation(data4), 1.0));

        std::cout << "All mean_absolute_deviation tests passed!" << std::endl;
    }

    {
        // CSVTable integration tests: load a small CSV and verify BasicStats on extracted columns
        const char* tmp_file = "tmp_stats_table.csv";
        std::ofstream out(tmp_file);
        out << "Name,Age,Height\n";
        out << "Alice,25,1.65\n";
        out << "Bob,30,1.80\n";
        out << "Charlie,22,1.75\n";
        out.close();

        try {
            CSVDataLoader loader;
            nr::CSVTable table(&loader, std::string(tmp_file));

            // Extract numeric columns
            auto ages = table.extract_column<int>("Age");
            auto heights = table.extract_column<double>("Height");

            // Ages: {25,30,22}
            assert(nr::min(ages) == 22);
            assert(nr::max(ages) == 30);
            assert(is_close(nr::arithmetic_mean(ages), (25+30+22)/3));
            assert(nr::median(ages) == 25);

            // Heights: {1.65, 1.80, 1.75}
            assert(is_close(nr::min(heights), 1.65));
            assert(is_close(nr::max(heights), 1.80));
            assert(is_close(nr::arithmetic_mean(heights), (1.65+1.80+1.75)/3.0));
            assert(is_close(nr::median(heights), 1.75));
        }
        catch (const std::exception &e) {
            std::cerr << "CSVTable BasicStats test failed: " << e.what() << std::endl;
            assert(false);
        }

        std::remove(tmp_file);
    }

    {
        // Tests for nr::dispersion (population variance)
        std::vector<double> data1 = {1.0, 2.0, 3.0, 4.0, 5.0};
        // mean = 3, variance = 2.0
        assert(is_close(nr::dispersion(data1), 2.0));
        assert(is_close(nr::dispersion(data1.begin(), data1.end()), 2.0));

        std::vector<double> data2 = {42.0, 42.0, 42.0};
        // all equal -> variance = 0
        assert(is_close(nr::dispersion(data2), 0.0));

        std::vector<int> data3 = {-1, 1};
        // mean = 0, variance = 1
        double expected3 = 1.0;
        assert(is_close(nr::dispersion(data3), expected3));
        assert(is_close(nr::dispersion(data3.begin(), data3.end()), expected3));

        // empty data should throw
        std::vector<int> empty;
        bool threw = false;
        try {
            nr::dispersion(empty);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        assert(threw);

        std::cout << "All dispersion tests passed!" << std::endl;

        // Tests for nr::dispersion (population variance)
        std::vector<double> data4 = {100.0, 107.0, 110.0, 113.0, 117.0, 121.0, 126.0, 129.0, 135.0, 138.0, 144.0, 148.0};
        // mean = 124.0, variance = 213.5
        assert(is_close(nr::dispersion(data4), 213.5, 1.0));
        assert(is_close(nr::dispersion(data4.begin(), data4.end()), 213.5, 1.0));

        // Tests for nr::dispersion (population variance)
        std::vector<double> data5 = {101.0, 107.0, 110.0, 113.0, 117.0, 115.0, 126.0, 129.0, 180.0, 138.0, 148.0, 148.0};
        // variance = 468.06
        std::cout << "Calculated mean: " << nr::dispersion(data5) << std::endl;
        assert(is_close(nr::dispersion(data5), 468.06, 0.01));
        assert(is_close(nr::dispersion(data5.begin(), data5.end()), 468.06, 0.01));

    }

    {
        // Tests for nr::standard_deviation (population standard deviation)
        std::vector<double> s1 = {1.0, 2.0, 3.0, 4.0, 5.0};
        double expected_s1 = std::sqrt(2.0); // variance = 2.0 -> stddev = sqrt(2)
        assert(is_close(nr::standard_deviation(s1), expected_s1));
        assert(is_close(nr::standard_deviation(s1.begin(), s1.end()), expected_s1));

        std::vector<double> s2 = {42.0, 42.0, 42.0};
        // all equal -> stddev = 0
        assert(is_close(nr::standard_deviation(s2), 0.0));

        std::vector<int> s3 = {-1, 1};
        // mean = 0, variance = 1 -> stddev = 1
        assert(is_close(nr::standard_deviation(s3), 1.0));
        assert(is_close(nr::standard_deviation(s3.begin(), s3.end()), 1.0));

        // empty data should throw
        std::vector<int> empty_sd;
        bool threw_sd = false;
        try {
            nr::standard_deviation(empty_sd);
        } catch (const std::invalid_argument&) {
            threw_sd = true;
        }
        assert(threw_sd);

        // Tests for nr::standard_deviation (population standard deviation)
        std::vector<double> s4 = {1.0, 2.0, 3.0, 4.0, 5.0, 13.0, 24.0, 10.0, 71.0};
        double expected_s4 = std::sqrt(441.73);
        assert(is_close(nr::standard_deviation(s4), expected_s4));
        assert(is_close(nr::standard_deviation(s4.begin(), s4.end()), expected_s4));

        std::cout << "All standard_deviation tests passed!" << std::endl;
    }

    std::cout << "All basic statistics tests passed!" << std::endl;

}