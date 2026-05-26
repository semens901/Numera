#include "NumericSampleTests.h"

void numeric_sample_tests()
{
    std::cout << "Running NumericSample tests..." << std::endl;

    double expected;
    double eps;

    {
        nr::NumericSample<double> vd;
        numeric_SizeToZero_test(vd);
        numeric_AddElements_test(vd);
        numeric_ClearElements_test(vd);
        numeric_CopyAndMove_test();
    }
    
    {
        nr::NumericSample<double> vd({1,2,3});
        numeric_RemoveElements_test(vd);
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
    assert(nr::Moduls::almostEqual(ns[0], 3.14, nr::Moduls::DEFAULT_EPS));
    assert(nr::Moduls::almostEqual(ns[1], 2.71, nr::Moduls::DEFAULT_EPS));
    assert(nr::Moduls::almostEqual(ns[2], 1.41, nr::Moduls::DEFAULT_EPS));
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
    assert(nr::Moduls::almostEqual(ns.arithmetic_mean(), expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: arithmetic mean is " << ns.arithmetic_mean() << "\n";
}

void numeric_ArithmeticMeanException_test(const nr::NumericSample<double> &ns)
{
    bool exception_thrown = false;
    try {
        ns.arithmetic_mean();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: arithmetic_mean throws exception for empty sample.\n";
}

void numeric_WeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights, double expected)
{
    auto result = ns.weighted_mean(weights);
    assert(nr::Moduls::almostEqual(result, expected, 1e-9));
    assert(result == expected);
    std::cout << "Test passed: weighted mean is " << result << "\n";
}

void numeric_GeometricMean_test(const nr::NumericSample<double> &ns, const double expected, const double eps)
{
    auto result = ns.geometric_mean();
    assert(nr::Moduls::almostEqual(result, expected, eps));
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

void numeric_HarmonicMean_test(const nr::NumericSample<double> &ns, double expected, double eps)
{
    auto result = ns.harmonic_mean();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: harmonic mean is " << result << "\n";
}

void numeric_LowerQuartile_test(const nr::NumericSample<int> &ns, double expected)
{
    auto result = ns.lower_quartile();
    assert(nr::Moduls::almostEqual(result, expected, 1e-9));
    std::cout << "Test passed: lower quartile is " << result << "\n";
}

void numeric_UpperQuartile_test(const nr::NumericSample<int> &ns, double expected)
{
    auto result = ns.upper_quartile();
    assert(nr::Moduls::almostEqual(result, expected, 1e-9));
    std::cout << "Test passed: upper quartile is " << result << "\n";
}

void numeric_Percentile_test(const nr::NumericSample<double> &ns, double p, double expected, double eps)
{
    auto result = ns.percentile(p);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: " << p << "th percentile is " << result << "\n";
}

void numeric_MeanAbsoluteDeviationDouble_test(const nr::NumericSample<double> &ns, double expected)
{
    auto result = ns.mean_absolute_deviation();
    assert(nr::Moduls::almostEqual(result, expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: mean absolute deviation is " << result << "\n";
}

void numeric_MeanAbsoluteDeviationInt_test(const nr::NumericSample<int> &ns, double expected)
{
    auto result = ns.mean_absolute_deviation();
    assert(nr::Moduls::almostEqual(result, expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: mean absolute deviation is " << result << "\n";
}

void numeric_Mode_test(const nr::NumericSample<int> &ns, std::optional<int> expected)
{
    auto result = ns.mode();
    if (expected.has_value()) {
        assert(result.has_value());
        assert(result.value() == expected.value());
        std::cout << "Test passed: mode is " << result.value() << "\n";
    } else {
        assert(!result.has_value());
        std::cout << "Test passed: no mode\n";
    }
}

void numeric_Modes_test(const nr::NumericSample<int> &ns, const std::vector<int> &expected)
{
    auto result = ns.modes();
    assert(result.size() == expected.size());
    std::sort(result.begin(), result.end());
    std::vector<int> sorted_expected = expected;
    std::sort(sorted_expected.begin(), sorted_expected.end());
    for (size_t i = 0; i < expected.size(); ++i) {
        assert(result[i] == sorted_expected[i]);
    }
    std::cout << "Test passed: modes are ";
    for (int mode : result) {
        std::cout << mode << " ";
    }
    std::cout << "\n";
}

void numeric_NoMode_test(const nr::NumericSample<int> &ns)
{
    auto result = ns.mode();
    assert(!result.has_value());
    std::vector<int> modes = ns.modes();
    assert(modes.empty());
    std::cout << "Test passed: no mode, modes size is " << modes.size() << "\n";
}

void numeric_Scope_test(const nr::NumericSample<int>& ns, double expected)
{
    auto result = ns.Scope();
    assert(nr::Moduls::almostEqual(result, expected, 1e-9));
    std::cout << "Test passed: scope is " << result << "\n";
}

void numeric_InterquartileRangeInt_test(const nr::NumericSample<int> &ns, double expected)
{
    auto result = ns.interquartile_range();
    assert(nr::Moduls::almostEqual(result, expected, 1e-9));
    std::cout << "Test passed: interquartile range is " << result << "\n";
}

void numeric_InterquartileRangeDouble_test(const nr::NumericSample<double> &ns, double expected)
{
    auto result = ns.interquartile_range();
    assert(nr::Moduls::almostEqual(result, expected, 1e-9));
    std::cout << "Test passed: interquartile range is " << result << "\n";
}
