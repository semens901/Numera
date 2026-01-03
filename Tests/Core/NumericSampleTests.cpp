#include "NumericSampleTests.h"

bool almostEqual(double a, double b, double eps = 1e-9)
{
    return std::abs(a - b) < eps;
}

bool is_close1(double a, double b, double epsilon = 0.0001) {
    return std::abs(a - b) < epsilon;
}

void numeric_sample_tests()
{
    {
        std::cout << "[TEST] NumericSample basic functionality\n";

        nr::NumericSample<double> vd;
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

        nr::NumericSample<double> vd1;
        nr::NumericSample<double> vd2 = vd1;
        nr::NumericSample<double> vd4 = std::move(vd2);
        assert(vd2.size() == 0);

        nr::NumericSample<double> vd5({1,2,3});
        vd5.remove_at(1);

        std::cout << "Test passed: basic functionality works correctly.\n";\
    }

    {
        std::cout << "[TEST] Adding elements\n";
        nr::NumericSample<double> vd;
        vd.add({1.0, 2.0, 3.0, 4.0, 5.0});
        assert(vd.size() == 5);
        std::cout << "Test passed: size is " << vd.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::NumericSample<double> vd2 = vd; // copy constructor
        assert(vd2.size() == 5);    
        std::cout << "Test passed: size is " << vd2.size() << "\n";
        
        std::cout << "[TEST] Copy and move semantics\n";
        nr::NumericSample<double> vd3;
        vd3 = vd; // copy assignment
        assert(vd3.size() == 5);    
        std::cout << "Test passed: size is " << vd3.size() << "\n";

        std::cout << "[TEST] Move semantics\n";
        nr::NumericSample<double> vd4 = std::move(vd); // move constructor
        assert(vd4.size() == 5);
        assert(vd.size() == 0); // vd should be empty after move
        std::cout << "Test passed: size is " << vd4.size() << "\n";    
        
        std::cout << "[TEST] Move semantics\n";
        nr::NumericSample<double> vd5;
        vd5 = std::move(vd2); // move assignment
        assert(vd5.size() == 5);
        assert(vd2.size() == 0); // vd2 should be empty after move
        std::cout << "Test passed: size is " << vd5.size() << "\n";

        std::cout << "[TEST] Removing elements\n";
        nr::NumericSample<double> vd6({1,2,3});
        vd6.remove_at(1); // remove element at index 1
        assert(vd6.size() == 2);
        assert(vd6[0] == 1);
        assert(vd6[1] == 3);
        std::cout << "Test passed: size is " << vd6.size() << "\n";
    }

    {
        
        std::cout << "[TEST] NumericSample stats funcs\n";
        nr::NumericSample<double> vc({1, 2, 3, 4});
        assert(vc.min() == 1);
        assert(vc.max() == 4);

        std::cout << "Test passed: min is " << vc.min() << ", max is " << vc.max() << "\n";
        
        assert(almostEqual(vc.arithmetic_mean(), 2.5));
        std::cout << "Test passed: arithmetic_mean is " << vc.arithmetic_mean() << "\n";
        /*
            assert(almostEqual(vc.median(), 2.5));
        */   
    }

    {
        nr::NumericSample<double> v({1.0, 2.0, 3.0});
        std::vector<double> w{1.0, 1.0, 1.0};

        double result = v.weighted_mean(w);
        assert(std::abs(result - 2.0) < 1e-9);
    }

    {
        nr::NumericSample<double> v({42.0});
        std::vector<double> w{10.0};

        double result = v.weighted_mean(w);
        assert(result == 42.0);
    }

    {
        nr::NumericSample<double> v({15, 10, 5, 90});
        std::vector <double> w{0.25, 0.20, 0.05, 0.50};

        double result = v.weighted_mean(w);
        assert(result == 51.0);
    }

    {
        nr::NumericSample<double> population({
            54, 63, 48, 29, 27, 32, 41
        });

        double result = population.geometric_mean();
        const double expected = 40.135109214786738;
        const double eps = 1e-6;

        assert(std::abs(result - expected) < eps);
    }

    {
        nr::NumericSample<double> data1({1.0, 3.0, 9.0});
        double gm1 = data1.geometric_mean();
        assert(std::abs(gm1 - 3.0) < 1e-9); // geometric arithmetic_mean = 3

        nr::NumericSample<double> data2({42});
        int gm2 = data2.geometric_mean();
        assert(gm2 == 42);

        nr::NumericSample<int> data3;
        bool exception_thrown = false;
        try {
            data3.geometric_mean();
        } catch (const std::invalid_argument&) {
            exception_thrown = true;
        }
        assert(exception_thrown);

        nr::NumericSample<double> data4({1.0, -2.0, 3.0});
        exception_thrown = false;
        try {
            data4.geometric_mean();
        } catch (const std::domain_error&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }

    {
        nr::NumericSample<double> population({54, 63, 48, 29, 27, 32, 41});

        double expected = 38.380368771744429; // calculated harmonic arithmetic_mean manually or using a calculator
        double result = population.harmonic_mean();
        // Using assert with tolerance for real numbers
        double eps = 1e-4; 
        assert(std::abs(result - expected) < eps);
    }

    {
        nr::NumericSample<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q1 = data.lower_quartile();

        assert(q1 == 29.0);
    }

    {
        nr::NumericSample<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q3 = data.upper_quartile();

        assert(q3 == 54.0);
    }

    {
        nr::NumericSample<double> data1({1.0, 2.0, 3.0, 4.0});
        double mean1 = data1.arithmetic_mean();
        assert(mean1 == 2.5); // (1+2+3+4)/4 = 2.5

        nr::NumericSample<int> data2({10});
        int mean2 = data2.arithmetic_mean();
        assert(mean2 == 10);

        nr::NumericSample<int> data3;
        bool exception_thrown = false;
        try {
            data3.arithmetic_mean();
        } catch (const std::invalid_argument&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }

    {
        nr::NumericSample<double> data({54, 63, 48, 29, 27, 32, 41});

        // Sorted data:
        // [27, 29, 32, 41, 48, 54, 63]

        double p25 = data.percentile(25);
        double p50 = data.percentile(50);
        double p75 = data.percentile(75);

        assert(std::abs(p25 - 30.5) < 1e-9);
        assert(std::abs(p50 - 41.0) < 1e-9);
        assert(std::abs(p75 - 51.0) < 1e-9);
    }

    {
        nr::NumericSample<int> data;
        data.reserve(100);

        for (int i = 100; i >= 1; --i)
            data.push_back(i);

        double p50 = data.percentile(50);

        assert(std::abs(p50 - 50.5) < 1e-9);
    }

    {
        std::vector<double> vec(100, 42.0);
        nr::NumericSample<double> data(vec);
        assert(data.percentile(10) == 42.0);
        assert(data.percentile(50) == 42.0);
        assert(data.percentile(90) == 42.0);
    }
    
    {
        nr::NumericSample<int> data({1, 2, 2, 3, 4});

        auto m = data.mode();
        assert(m.has_value());
        assert(*m == 2);

        auto ms = data.modes();
        assert(ms.size() == 1);
        assert(ms[0] == 2);
    }

    {
        nr::NumericSample<int> data({1, 2, 3, 4, 5});

        auto m = data.mode();
        assert(!m.has_value());

        auto ms = data.modes();
        assert(ms.empty());
    }

    {
        nr::NumericSample<int> data({1, 1, 2, 2, 3});

        auto m = data.mode();
        assert(!m.has_value());

        auto ms = data.modes();
        assert(ms.size() == 2);

        std::sort(ms.begin(), ms.end());
        assert(ms[0] == 1);
        assert(ms[1] == 2);
    }

    {
        nr::NumericSample<int> data({1, 2, 3, 4, 5});

        auto result = data.Scope();
        assert(result == 4); // 5 - 1
    }

    {
        nr::NumericSample<int> data({10, 3, 7, 1, 9});

        auto result = data.Scope();
        assert(result == 9); // 10 - 1
    }

    {
        nr::NumericSample<int> data({-10, -5, -3, -20});

        auto result = data.Scope();
        assert(result == 17); // -3 - (-20)
    }

    {
        nr::NumericSample<int> data({-5, 0, 10});

        auto result = data.Scope();
        assert(result == 15); // 10 - (-5)
    }

    {
        nr::NumericSample<int> data1({1, 2, 3, 4, 5, 6, 7, 8});
        assert(is_close1(data1.interquartile_range(), 4.0));

        nr::NumericSample<int> data2({9, 1, 8, 2, 7, 3, 6, 4, 5}); // Неотсортированные
        assert(is_close1(data2.interquartile_range(), 5.0));

        nr::NumericSample<double> data3({1.0, 2.0, 3.0, 4.0});
        assert(is_close1(data3.interquartile_range(), 2.0));


        std::cout << "All interquartile_range tests passed!" << std::endl;
    }

    {
        // Test 1: Simple Dataset
        // Data: {2, 2, 3, 4, 14}, Mean = 5
        // Deviations: |2-5|=3, |2-5|=3, |3-5|=2, |4-5|=1, |14-5|=9
        // Sum of deviations: 18. MAD = 18 / 5 = 3.6
        nr::NumericSample<int> data1({2, 2, 3, 4, 14});
        assert(is_close1(data1.mean_absolute_deviation(), 3.6));

        // Test 2: All elements are the same
        // Data: {5, 5, 5, 5}, Mean = 5
        // Deviations are all equal to 0. MAD = 0
        nr::NumericSample<double> data2({5.0, 5.0, 5.0, 5.0});
        assert(is_close1(data2.mean_absolute_deviation(), 0.0));

        // Test 3: Negative Values
        // Data: {-10, 10}, Mean = 0
        // Deviations: |-10-0|=10, |10-0|=10
        // Sum: 20. MAD = 20 / 2 = 10.0
        nr::NumericSample<int> data3({-10, 10});
        assert(is_close1(data3.mean_absolute_deviation(), 10.0));

        // Test 4: Fractional Values
        // Data: {1.5, 2.5, 3.5, 4.5}, Mean = 3.0
        // Deviations: 1.5, 0.5, 0.5, 1.5. Sum: 4.0. MAD = 4 / 4 = 1.0
        nr::NumericSample<double> data4({1.5, 2.5, 3.5, 4.5});
        assert(is_close1(data4.mean_absolute_deviation(), 1.0));

        std::cout << "All mean_absolute_deviation tests passed!" << std::endl;
    }
}