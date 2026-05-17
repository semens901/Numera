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
    std::cout << "Running NumericSample tests..." << std::endl;
    nr::NumericSample<double> vd;
    numeric_SizeToZero_test(vd);
    numeric_AddElements_test(vd);
    numeric_ClearElements_test(vd);
    numeric_CopyAndMove_test();

    nr::NumericSample<double> vd5({1,2,3});
    numeric_RemoveElements_test(vd5);

    nr::NumericSample<double> vc({1, 2, 3, 4});
    numeric_Min_test(vc, 1); // should be 1
    numeric_Max_test(vc, 4); // should be 4
    numeric_ArithmeticMean_test(vc, 2.5); // should be 2.5 

    std::cout << "[TEST] Weighted mean\n";
    nr::NumericSample<double> v({1.0, 2.0, 3.0});
    std::vector<double> w{1.0, 1.0, 1.0};

    numeric_WeightedMean_test(v, w, 2.0); // should be 2.0

    nr::NumericSample<double> v1({42.0});
    std::vector<double> w1{10.0};

    numeric_WeightedMean_test(v1, w1, 42.0); // should be 42.0


    nr::NumericSample<double> v2({15, 10, 5, 90});
    std::vector <double> w2{0.25, 0.20, 0.05, 0.50};

    numeric_WeightedMean_test(v2, w2, 51.0); // should be 51.0

    std::cout << "[TEST] Geometric mean\n";
    nr::NumericSample<double> population({
        54, 63, 48, 29, 27, 32, 41
    });

    double expected = 40.135109214786738;
    double eps = 1e-6;

    numeric_GeometricMean_test(population, expected, eps);

    std::cout << "[TEST] Geometric mean with iterators\n";
    nr::NumericSample<double> data1({1.0, 3.0, 9.0});
    expected = 3.0;
    eps = 1e-9;
    numeric_GeometricMean_test(data1, expected, eps); // geometric mean should be 3.0

    nr::NumericSample<double> data2({42});
    numeric_GeometricMean_test(data2, 42.0, eps); // geometric mean of a single value should be that value
    

    nr::NumericSample<int> data3;
    numeric_GeometricMeanIntException_test(data3); // should throw exception for empty sample

    nr::NumericSample<double> data4;
    numeric_GeometricMeanDoubleException_test(data4); // should throw exception for non-positive value


    {
        std::cout << "[TEST] Harmonic mean\n";
        nr::NumericSample<double> population({54, 63, 48, 29, 27, 32, 41});

        double expected = 38.380368771744429; // calculated harmonic arithmetic_mean manually or using a calculator
        double result = population.harmonic_mean();
        // Using assert with tolerance for real numbers
        double eps = 1e-4; 
        assert(std::abs(result - expected) < eps);
        std::cout << "Test passed: harmonic_mean is " << result << "\n";
    }

    {
        std::cout << "[TEST] Lower quartile\n";
        nr::NumericSample<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q1 = data.lower_quartile();

        assert(q1 == 29.0);
        std::cout << "Test passed: lower_quartile is " << q1 << "\n";
    }

    {
        std::cout << "[TEST] Upper quartile\n";
        nr::NumericSample<int> data({54, 63, 48, 29, 27, 32, 41});

        auto q3 = data.upper_quartile();

        assert(q3 == 54.0);
        std::cout << "Test passed: upper_quartile is " << q3 << "\n";
    }

    {
        std::cout << "[TEST] Arithmetic mean\n";
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
        std::cout << "Test passed: arithmetic_mean works correctly.\n";
    }

    {
        std::cout << "[TEST] Percentiles\n";
        nr::NumericSample<double> data({54, 63, 48, 29, 27, 32, 41});

        // Sorted data:
        // [27, 29, 32, 41, 48, 54, 63]

        double p25 = data.percentile(25);
        double p50 = data.percentile(50);
        double p75 = data.percentile(75);

        assert(std::abs(p25 - 30.5) < 1e-9);
        assert(std::abs(p50 - 41.0) < 1e-9);
        assert(std::abs(p75 - 51.0) < 1e-9);
        std::cout << "Test passed: percentiles are p25=" << p25 << ", p50=" << p50 << ", p75=" << p75 << "\n";
    }

    {
        std::cout << "[TEST] Large dataset percentiles\n";
        nr::NumericSample<int> data;
        data.reserve(100);

        for (int i = 100; i >= 1; --i)
            data.push_back(i);

        double p50 = data.percentile(50);

        assert(std::abs(p50 - 50.5) < 1e-9);
        std::cout << "Test passed: large dataset percentiles work correctly.\n";
    }

    {
        std::cout << "[TEST] Uniform dataset percentiles\n";
        std::vector<double> vec(100, 42.0);
        nr::NumericSample<double> data(vec);
        assert(data.percentile(10) == 42.0);
        assert(data.percentile(50) == 42.0);
        assert(data.percentile(90) == 42.0);
        std::cout << "Test passed: uniform dataset percentiles work correctly.\n";
    }
    
    {
        std::cout << "[TEST] Mode and modes\n";
        nr::NumericSample<int> data({1, 2, 2, 3, 4});

        auto m = data.mode();
        assert(m.has_value());
        assert(*m == 2);

        auto ms = data.modes();
        assert(ms.size() == 1);
        assert(ms[0] == 2);
        std::cout << "Test passed: mode is " << *m << ", modes size is " << ms.size() << "\n";
    }

    {
        std::cout << "[TEST] No mode\n";
        nr::NumericSample<int> data({1, 2, 3, 4, 5});

        auto m = data.mode();
        assert(!m.has_value());

        auto ms = data.modes();
        assert(ms.empty());
        std::cout << "Test passed: no mode, modes size is " << ms.size() << "\n";
    }

    {
        std::cout << "[TEST] Multiple modes\n";
        nr::NumericSample<int> data({1, 1, 2, 2, 3});

        auto m = data.mode();
        assert(!m.has_value());

        auto ms = data.modes();
        assert(ms.size() == 2);

        std::sort(ms.begin(), ms.end());
        assert(ms[0] == 1);
        assert(ms[1] == 2);
        std::cout << "Test passed: multiple modes, modes size is " << ms.size() << "\n";
    }

    {
        std::cout << "[TEST] All values are modes\n";
        nr::NumericSample<int> data({1, 2, 3, 4, 5});

        auto result = data.Scope();
        assert(result == 4); // 5 - 1
        std::cout << "Test passed: all values are modes, scope is " << result << "\n";
    }

    {
        std::cout << "[TEST] Scope\n";
        nr::NumericSample<int> data({10, 3, 7, 1, 9});

        auto result = data.Scope();
        assert(result == 9); // 10 - 1
        std::cout << "Test passed: scope is " << result << "\n";
    }

    {
        std::cout << "[TEST] Scope with negative values\n";
        nr::NumericSample<int> data({-10, -5, -3, -20});

        auto result = data.Scope();
        assert(result == 17); // -3 - (-20)
        std::cout << "Test passed: scope with negative values is " << result << "\n";
    }

    {
        std::cout << "[TEST] Scope with NumericSample\n";
        nr::NumericSample<int> data({-5, 0, 10});

        auto result = data.Scope();
        assert(result == 15); // 10 - (-5)
        std::cout << "Test passed: scope with NumericSample is " << result << "\n";
    }

    {
        std::cout << "[TEST] Interquartile range\n";
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

    std::cout << "All NumericSample tests passed!" << std::endl;
}

void numeric_SizeToZero_test(const nr::NumericSample<double>& ns)
{
    assert(ns.size() == 0);
    assert(ns.empty());
    std::cout << "Test passed: size is zero and sample is empty.\n";
}

void numeric_AddElements_test(nr::NumericSample<double>& ns)
{
    ns.add(3.14);
    ns.add(2.71);
    ns.add(1.41);

    assert(ns.size() == 3);
    assert(!ns.empty());
    assert(almostEqual(ns[0], 3.14));
    assert(almostEqual(ns[1], 2.71));
    assert(almostEqual(ns[2], 1.41));
    std::cout << "Test passed: elements added correctly, size is " << ns.size() << "\n";
}

void numeric_ClearElements_test(nr::NumericSample<double>& ns)
{
    ns.clear();
    assert(ns.size() == 0);
    assert(ns.empty());
    std::cout << "Test passed: elements cleared, size is " << ns.size() << "\n";
}

void numeric_CopyAndMove_test()
{
     nr::NumericSample<double> vd1;
    nr::NumericSample<double> vd2 = vd1;
    vd2.add(3.14);
    vd2.add(2.71);
    vd2.add(1.41);
    nr::NumericSample<double> vd4 = std::move(vd2);
    assert(vd4.size() == 3);
    std::cout << "Test passed: copy and move semantics work correctly, moved size is " << vd4.size() << "\n";
}

void numeric_RemoveElements_test(nr::NumericSample<double> ns)
{
    ns.remove_at(1);
    assert(ns.size() == 2);
    assert(ns[0] == 1);
    assert(ns[1] == 3);
    std::cout << "Test passed: elements removed correctly, size is " << ns.size() << "\n";
}

void numeric_Min_test(const nr::NumericSample<double>& ns, double expected)
{
    assert(ns.min() == expected);
    std::cout << "Test passed: minimum value is " << ns.min() << "\n";
}

void numeric_Max_test(const nr::NumericSample<double>& ns, double expected)
{
    assert(ns.max() == expected);
    std::cout << "Test passed: maximum value is " << ns.max() << "\n";
}

void numeric_ArithmeticMean_test(const nr::NumericSample<double>& ns, double expected)
{
    assert(almostEqual(ns.arithmetic_mean(), expected));
    std::cout << "Test passed: arithmetic mean is " << ns.arithmetic_mean() << "\n";
}

void numeric_WeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights, double expected)
{
    double result = ns.weighted_mean(weights);
    assert(std::abs(result - expected) < 1e-9);
    assert(result == expected);
    std::cout << "Test passed: weighted mean is " << result << "\n";
}

void numeric_GeometricMean_test(const nr::NumericSample<double> &ns, const double expected, const double eps)
{
    double result = ns.geometric_mean();
    assert(std::abs(result - expected) < eps);
    std::cout << "Test passed: geometric mean is " << result << "\n";
}

void numeric_GeometricMeanIntException_test(const nr::NumericSample<int>& ns)
{
    bool exception_thrown = false;
    try {
        ns.geometric_mean();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: geometric_mean throws exception for empty sample.\n";
}

void numeric_GeometricMeanDoubleException_test(const nr::NumericSample<double>& ns)
{
    bool exception_thrown = false;
    try {
        ns.geometric_mean();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: geometric_mean throws exception for empty sample.\n";
}
