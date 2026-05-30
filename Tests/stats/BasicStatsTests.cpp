#include "BasicStatsTests.h"

// almostEqual: compare two floating-point values for approximate equality.
// Returns true when the absolute difference between `a` and `b` is
// strictly less than `epsilon`. Useful in tests to avoid relying on
// exact equality for results of floating-point computations.

void basic_stats_tests()
{
    std::cout << "[TESTS] Basic statistics\n";
    
    BasicStats_Min_tests();

    BasicStats_Max_tests();

    BasicStats_WeightedMean_tests();

    BasicStats_GeometricMean_tests();

    BasicStats_HarmonicMean_tests();

    BasicStats_LowerQuartile_tests();

    BasicStats_UpperQuartile_tests();

    BasicStats_ArithmeticMean_tests();

    BasicStats_Median_tests();

    BasicStats_Percentile_tests();

    BasicStats_Mode_tests();
    
    BasicStats_Modes_tests();

    BasicStats_Scope_tests();
    
    BasicStats_InterquartileRange_tests();
    
    BasicStats_MeanAbsoluteDeviation_tests();

    BasicStats_Dispersion_tests();
    
    BasicStats_StandardDeviation_tests();
    

    std::cout << "All basic statistics tests passed!" << std::endl;

}

void BasicStats_Min_tests()
{
    {
        nr::NumericSample<double> vc({1, 2, 3, 4});
        double expected = 1;
        BasicStats_Min_test(vc, expected); // should be 1
        nr::NumericSample<double> emptySample;
        BasicStats_ExceptionTrue_In_Min_test(emptySample);
    }
}

void BasicStats_Min_test(const nr::NumericSample<double>& ns, double expected)
{
    assert(ns.min() == expected);
    std::cout << "Test passed: minimum value is " << ns.min() << "\n";
}

void BasicStats_ExceptionTrue_In_Min_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.min();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: min() threw exception for empty sample\n";
}

void BasicStats_Max_tests()
{
     {
        nr::NumericSample<double> vc({1, 2, 3, 4});
        double expected = 4;
        BasicStats_Max_test(vc, expected); // should be 4
        nr::NumericSample<double> emptySample;
        BasicStats_ExceptionTrue_In_Max_test(emptySample);
    }
}

void BasicStats_Max_test(const nr::NumericSample<double>& ns, double expected)
{
    assert(ns.max() == expected);
    std::cout << "Test passed: maximum value is " << ns.max() << "\n";
}

void BasicStats_ExceptionTrue_In_Max_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.max();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: max() threw exception for empty sample\n";
}

void BasicStats_NumericSampleWeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights, double expected)
{
    auto result = ns.weighted_mean(weights);
    assert(nr::Moduls::almostEqual(result, expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: weighted mean is " << result << "\n";
}

void BasicStats_IteratorWeightedMean_test(std::vector<double>::iterator begin_data, std::vector<double>::iterator end_data, std::vector<double>::iterator begin_weights, std::vector<double>::iterator end_weights, double expected)
{
    auto result = nr::weighted_mean(begin_data, end_data, begin_weights, end_weights);
    assert(nr::Moduls::almostEqual(result, expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: weighted mean is " << result << "\n";
}

void BasicStats_IteratorWithNoWeightedEndWeightedMean_test(std::vector<double>::iterator begin_data, std::vector<double>::iterator end_data, std::vector<double>::iterator begin_weights, double expected)
{
    auto result = nr::weighted_mean(begin_data, end_data, begin_weights);
    assert(nr::Moduls::almostEqual(result, expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: weighted mean is " << result << "\n";
}

void BasicStats_WeightedMean_tests()
{
    {
        std::vector<double> v{1.0, 2.0, 3.0};
        std::vector<double> w{1.0, 1.0, 1.0};
        double eps = 2.0;
        BasicStats_VectorWeightedMean_test(v, w, eps);
    }

    {
        std::vector<double> v{42.0};
        std::vector<double> w{10.0};
        double eps = 42.0;
        BasicStats_VectorWeightedMean_test(v, w, eps);
    }

    {
        std::vector<double> v{15, 10, 5, 90};
        std::vector <double> w{0.25, 0.20, 0.05, 0.50};
        double eps = 51.0;
        BasicStats_VectorWeightedMean_test(v, w, eps);
        BasicStats_IteratorWeightedMean_test(v.begin(), v.end(), w.begin(), w.end(), eps);
        
    }

    {
        nr::NumericSample<double> v({15, 10, 5, 90});
        std::vector <double> w{0.25, 0.20, 0.05, 0.50};
        double eps = 51.0;
        BasicStats_NumericSampleWeightedMean_test(v, w, eps);
    }

    {
        nr::NumericSample<double> v({15, 10, 5, 90});
        std::vector<double> v1({15, 10, 5, 90});
        std::vector <double> w{0.25, 0.20, 0.05};
        double eps = 51.0;
        BasicStats_ExceptionTrue_In_VectorWeightedMean_test(v1, w);
        BasicStats_ExceptionTrue_In_NumericSampleWeightedMean_test(v, w);
        BasicStats_ExceptionTrue_In_IteratorWeightedMean_test(v1.begin(), v1.end(), w.begin(), w.end());
    }
}

void BasicStats_VectorWeightedMean_test(const std::vector<double> &vec, const std::vector<double> &weights, double expected)
{
    auto result = nr::weighted_mean(vec, weights);
    assert(nr::Moduls::almostEqual(result, expected, nr::Moduls::DEFAULT_EPS));
    std::cout << "Test passed: weighted mean is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_VectorWeightedMean_test(const std::vector<double>& vec, const std::vector<double>& weights)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::weighted_mean(vec, weights);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void BasicStats_ExceptionTrue_In_NumericSampleWeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.weighted_mean(weights);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void BasicStats_ExceptionTrue_In_IteratorWeightedMean_test(std::vector<double>::iterator beginData, std::vector<double>::iterator endData, std::vector<double>::iterator beginWeights, std::vector<double>::iterator endWeights)
{
    // beginData must be == endData
    bool exception_thrown = false;
    try {
        nr::weighted_mean(beginData, endData, beginWeights, endWeights);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void BasicStats_NumericSampleGeometricMean_test(const nr::NumericSample<double>& ns, double expected, double eps)
{
    auto result = ns.geometric_mean();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: geometric mean is " << result << "\n";
}

void BasicStats_GeometricMean_tests()
{
    {
        std::vector<double> population{
            54, 63, 48, 29, 27, 32, 41
        };
        double expected = 40.135109214786738;
        double eps = 1e-6;
        BasicStats_VectorGeometricMean_test(population, expected, eps);

        nr::NumericSample<double> populationSample(population.begin(), population.end());
        BasicStats_NumericSampleGeometricMean_test(populationSample, expected, eps);
    }

    {
        std::vector<double> data1 = {1.0, 3.0, 9.0};
        double expected = 3.0;
        double eps = nr::Moduls::DEFAULT_EPS;

        BasicStats_IteratorGeometricMean_test(data1.begin(), data1.end(), expected, eps); // geometric mean should be 3.0

        expected = 42.0;
        std::vector<double> data2 = {42};
        BasicStats_IteratorGeometricMean_test(data2.begin(), data2.end(), expected, eps); // geometric mean should be 42.0
    }

    {
        std::vector<double> data = {1.0, -2.0, 3.0};
        BasicStats_ExceptionTrue_In_VectorGeometricMean_test(data);

        nr::NumericSample<double> n(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_NumericGeometricMean_test(n);

        std::vector<double> data3(data);
        BasicStats_ExceptionTrue_In_IteratorGeometricMean_test(data3.begin(), data3.end());
        std::vector<double> data4 = {0.0, 1.0, 2.0};
    }
}

void BasicStats_VectorGeometricMean_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::geometric_mean(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: geometric mean is " << result << "\n";
}

void BasicStats_IteratorGeometricMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::geometric_mean(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: geometric mean is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_IteratorGeometricMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin must be == end
    bool exception_thrown = false;
    try {
        nr::geometric_mean(begin, end);
    } catch (const std::domain_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: geometric mean threw exception for invalid input\n";
}

void BasicStats_ExceptionTrue_In_NumericGeometricMean_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        nr::geometric_mean(ns);
    } catch (const std::domain_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: geometric mean threw exception for invalid input\n";
}

void BasicStats_ExceptionTrue_In_VectorGeometricMean_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::geometric_mean(vec);
    } catch (const std::domain_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: geometric mean threw exception for invalid input\n";
}

void BasicStats_NumericSampleHarmonicMean_test(const nr::NumericSample<double>& ns, double expected, double eps)
{
    auto result = ns.harmonic_mean();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: harmonic mean is " << result << "\n";
}

void BasicStats_HarmonicMean_tests()
{
    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, 41};
        nr::NumericSample<double> populationSample(population.begin(), population.end());
        double expected = 38.380368771744429; // calculated harmonic arithmetic_mean manually or using a calculator
        double eps = 1e-4; 

        BasicStats_VectorHarmonicMean_test(population, expected, eps);
        BasicStats_NumericSampleHarmonicMean_test(populationSample, expected, eps);
    }

    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, 41};

        double expected = 38.380368771744429; // calculated harmonic arithmetic_mean manually or using a calculator
        double eps = 1e-4; 
        BasicStats_IteratorHarmonicMean_test(population.begin(), population.end(), expected, eps);
    }

    {
        std::vector<double> population{54, 63, 48, 29, 27, 32, -41};
        BasicStats_ExceptionTrue_In_VectorHarmonicMean_test(population);
        
        nr::NumericSample<double> populationSample(population.begin(), population.end());
        BasicStats_ExceptionTrue_In_NumericHarmonicMean_test(populationSample);
        
        std::vector<double> populationCopy(population);
        BasicStats_ExceptionTrue_In_IteratorHarmonicMean_test(populationCopy.begin(), populationCopy.end());
    }
}

void BasicStats_VectorHarmonicMean_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::harmonic_mean(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: harmonic mean is " << result << "\n";
}

void BasicStats_IteratorHarmonicMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::harmonic_mean(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: harmonic mean is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_NumericHarmonicMean_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.harmonic_mean();
    } catch (const std::domain_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: harmonic mean threw exception for invalid input\n";
}

void BasicStats_ExceptionTrue_In_IteratorHarmonicMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{   
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::harmonic_mean(begin, end);
    } catch (const std::domain_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: harmonic mean threw exception for invalid input\n";
}

void BasicStats_ExceptionTrue_In_VectorHarmonicMean_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::harmonic_mean(vec);
    } catch (const std::domain_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: harmonic mean threw exception for invalid input\n";
}

void BasicStats_LowerQuartile_tests()
{
    {
        std::vector<double> data{54, 63, 48, 29, 27, 32, 41};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double expected = 29.0;
        double eps = nr::Moduls::DEFAULT_EPS;

        BasicStats_VectorLowerQuartile_test(data, expected, eps);
        BasicStats_NumericSampleLowerQuartile_test(dataSample, expected, eps);
        BasicStats_IteratorLowerQuartile_test(data.begin(), data.end(), expected, eps);
    }

    {
        std::vector<double> data{};
        BasicStats_ExceptionTrue_In_VectorLowerQuartile_test(data);

        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_NumericSampleLowerQuartile_test(dataSample);

        std::vector<double> dataCopy(data);
        BasicStats_ExceptionTrue_In_IteratorLowerQuartile_test(dataCopy.begin(), dataCopy.end());
    }
}

void BasicStats_VectorLowerQuartile_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::lower_quartile(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: lower quartile is " << result << "\n";
}

void BasicStats_NumericSampleLowerQuartile_test(const nr::NumericSample<double>& ns, double expected, double eps)
{
    auto result = ns.lower_quartile();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: lower quartile is " << result << "\n";
}

void BasicStats_IteratorLowerQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::lower_quartile(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: lower quartile is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_VectorLowerQuartile_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::lower_quartile(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: lower quartile threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleLowerQuartile_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.lower_quartile();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: lower quartile threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorLowerQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // vegin == end must be empty
    bool exception_thrown = false;
    try {
        nr::lower_quartile(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: lower quartile threw exception for empty input\n";
}

void BasicStats_UpperQuartile_tests()
{
    {
        std::vector<double> data{54, 63, 48, 29, 27, 32, 41};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double eps = nr::Moduls::DEFAULT_EPS;
        double expected = 54.0;

        BasicStats_VectorUpperQuartile_test(data, expected, eps);
        BasicStats_NumericSampleUpperQuartile_test(dataSample, expected, eps);
        BasicStats_IteratorUpperQuartile_test(data.begin(), data.end(), expected, eps);
    }

    {
        std::vector<double> data{};
        BasicStats_ExceptionTrue_In_VectorUpperQuartile_test(data);

        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_NumericSampleUpperQuartile_test(dataSample);

        std::vector<double> dataCopy(data);
        BasicStats_ExceptionTrue_In_IteratorUpperQuartile_test(dataCopy.begin(), dataCopy.end());
    }
}

void BasicStats_VectorUpperQuartile_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::upper_quartile(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: upper quartile is " << result << "\n";
}

void BasicStats_NumericSampleUpperQuartile_test(const nr::NumericSample<double>& ns, double expected, double eps)
{
    auto result = ns.upper_quartile();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: upper quartile is " << result << "\n";
}

void BasicStats_IteratorUpperQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::upper_quartile(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: upper quartile is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_VectorUpperQuartile_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::upper_quartile(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: upper quartile threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorUpperQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::upper_quartile(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: upper quartile threw exception for empty input\n";
}

void BasicStats_NumericSampleArithmeticMean_test(const nr::NumericSample<double>& ns, double expected, double eps)
{
    auto result = ns.arithmetic_mean();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: arithmetic mean is " << result << "\n";
}

void BasicStats_ArithmeticMean_tests()
{
    {
        std::vector<double> data1 = {1.0, 2.0, 3.0, 4.0};
        nr::NumericSample<double> dataSample(data1.begin(), data1.end());
        double eps = 1e-9;
        double expected = 2.5;


        BasicStats_VectorArithmeticMean_test(data1, expected, eps); // arithmetic mean should be 2.5
        BasicStats_NumericSampleArithmeticMean_test(dataSample, expected, eps);
        BasicStats_IteratorArithmeticMean_test(data1.begin(), data1.end(), expected, eps);
    }

    {
        std::vector<double> data3;
        nr::NumericSample<double> dataSample3(data3.begin(), data3.end());

        BasicStats_ExceptionTrue_In_VectorArithmeticMean_test(data3);
        BasicStats_ExceptionTrue_In_NumericArithmeticMean_test(dataSample3);
        BasicStats_ExceptionTrue_In_IteratorArithmeticMean_test(data3.begin(), data3.end());
    }
}

void BasicStats_VectorArithmeticMean_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::arithmetic_mean(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: arithmetic mean is " << result << "\n";
}

void BasicStats_IteratorArithmeticMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::arithmetic_mean(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: arithmetic mean is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_IteratorArithmeticMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    bool exception_thrown = false;
    try {
        nr::arithmetic_mean(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: arithmetic mean threw exception for empty input\n";
}

void BasicStats_Median_tests()
{
    {
        std::vector<double> data1 = {3.0, 1.0, 4.0, 2.0, 5.0};
        nr::NumericSample<double> dataSample(data1.begin(), data1.end());
        double eps = 1e-9;
        double expected = 3.0;

        BasicStats_VectorMedian_test(data1, expected, eps); // median should be 3.0
        BasicStats_NumericSampleMedian_test(dataSample, expected, eps);
        BasicStats_IteratorMedian_test(data1.begin(), data1.end(), expected, eps);
    }

    {
        std::vector<double> data4;
        nr::NumericSample<double> dataSample4(data4.begin(), data4.end());
        BasicStats_ExceptionTrue_In_VectorMedian_test(data4);
        BasicStats_ExceptionTrue_In_NumericSampleMedian_test(dataSample4);
        BasicStats_ExceptionTrue_In_IteratorMedian_test(data4.begin(), data4.end());
    }
}

void BasicStats_VectorMedian_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::median(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: median is " << result << "\n";
}

void BasicStats_NumericSampleMedian_test(const nr::NumericSample<double>& ns, double expected, double eps)
{
    auto result = ns.median();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: median is " << result << "\n";
}

void BasicStats_IteratorMedian_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::median(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: median is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_VectorMedian_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::median(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: median threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorMedian_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::median(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: median threw exception for empty input\n";
}

void BasicStats_Percentile_tests()
{
    {
        std::vector<double> data{54, 63, 48, 29, 27, 32, 41};

        // Sorted data:
        // [27, 29, 32, 41, 48, 54, 63]
        double expected = 30.5;
        double perc = 25;
        double eps = nr::Moduls::DEFAULT_EPS;
        BasicStats_VectorPercentile_test(data, perc, expected, eps);
        
        perc = 50;
        expected = 41.0;
        BasicStats_VectorPercentile_test(data, perc, expected, eps);
        
        perc = 75;
        expected = 51.0;
        BasicStats_VectorPercentile_test(data, perc, expected, eps);
    }

    {
        std::vector<double> data;
        data.reserve(100);

        for (int i = 100; i >= 1; --i)
            data.push_back(i);

        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double p = 50;
        double expected = 50.5;
        double eps = nr::Moduls::DEFAULT_EPS;
        BasicStats_NumericSamplePercentile_test(dataSample, p, expected, eps);

        BasicStats_IteratorPercentile_test(data.begin(), data.end(), p, expected, eps);
    }

    {
        std::vector<double> data;
        BasicStats_ExceptionTrue_In_VectorPercentile_test(data);
        
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_NumericSamplePercentile_test(dataSample);
    
        BasicStats_ExceptionTrue_In_IteratorPercentile_test(data.begin(), data.end());
    }
}

void BasicStats_VectorPercentile_test(const std::vector<double> &vec, double p, double expected, double eps)
{
    auto result = nr::percentile(vec, p);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Percentile is " << result << "\n";
}

void BasicStats_NumericSamplePercentile_test(const nr::NumericSample<double>& ns, double p, double expected, double eps)
{
    auto result = ns.percentile(p);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Percentile is " << result << "\n";
}

void BasicStats_IteratorPercentile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double p, double expected, double eps)
{
    auto result = nr::percentile(begin, end, p);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Percentile is " << result << "\n";
}

void BasicStats_ExceptionTrue_In_VectorPercentile_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::percentile(vec, 25);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: percentile threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSamplePercentile_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.percentile(25);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: percentile threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorPercentile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::percentile(begin, end, 25);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: percentile threw exception for empty input\n";
}

void BasicStats_Mode_tests()
{
    {
        std::vector<double> data{1, 2, 2, 3, 4};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double expected = 2;
        BasicStats_VectorMode_test(data, expected);
        BasicStats_NumericSampleMode_test(dataSample, expected);
        BasicStats_IteratorMode_test(data.begin(), data.end(), expected);
    }

    {
        std::vector<double> data{1, 2, 3, 4, 5};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_VectorModeHasValueFalse_test(data);
        BasicStats_NumericSampleModeHasValueFalse_test(dataSample);
        BasicStats_IteratorModeHasValueFalse_test(data.begin(), data.end());
    }
}

void BasicStats_VectorMode_test(const std::vector<double> &ns, double expected)
{
    auto result = *nr::mode(ns);
    assert(result == expected);
    std::cout << "Test passed: mode is " << result << "\n";
}

void BasicStats_NumericSampleMode_test(const nr::NumericSample<double>& ns, double expected)
{
    auto result = *ns.mode();
    assert(result == expected);
    std::cout << "Test passed: mode is " << result << "\n";
}

void BasicStats_IteratorMode_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected)
{
    auto result = *nr::mode(begin, end);
    assert(result == expected);
    std::cout << "Test passed: mode is " << result << "\n";
}

void BasicStats_VectorModeHasValueFalse_test(const std::vector<double>& vec)
{
    auto result = nr::mode(vec);
    assert(!result.has_value());
    std::cout << "Test passed: mode is empty" << "\n";
}

void BasicStats_NumericSampleModeHasValueFalse_test(const nr::NumericSample<double>& ns)
{
    auto result = ns.mode();
    assert(!result.has_value());
    std::cout << "Test passed: mode is empty" << "\n";
}

void BasicStats_IteratorModeHasValueFalse_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    auto result = nr::mode(begin, end);
    assert(!result.has_value());
    std::cout << "Test passed: mode is empty" << "\n";
}

void BasicStats_Modes_tests()
{
    {
        std::vector<double> data{1, 2, 2, 3, 4};
        std::vector<double> expected{2};
        BasicStats_VectorModes_test(data, expected);
    }

    {
        std::vector<double> data{1, 2, 3, 4, 5};
        std::vector<double> expected;
        BasicStats_VectorModes_test(data, expected);
    }

    {
        std::vector<double> data{1, 1, 2, 2, 3};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        std::vector<double> expected{1,2};

        BasicStats_VectorModes_test(data, expected);
        BasicStats_NumericSampleModes_test(dataSample, expected);
        BasicStats_IteratorModes_test(data.begin(), data.end(), expected);
    }

    {
        std::vector<double> data{1, 1, 2, 2, 3, 3};
        std::vector<double> expected{1,2,3};
        BasicStats_VectorModes_test(data, expected);
    }
}

void BasicStats_VectorModes_test(const std::vector<double> &vec, const std::vector<double> &expected)
{
    auto result = nr::modes(vec);
    for(size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i] == expected[i]);
    }
    std::cout << "Test passed: modes" << "\n";
}

void BasicStats_NumericSampleModes_test(const nr::NumericSample<double>& ns, const std::vector<double>& expected)
{
    auto result = ns.modes();
    for(size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i] == expected[i]);
    }
    std::cout << "Test passed: modes" << "\n";
}

void BasicStats_IteratorModes_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, std::vector<double> expected)
{
    auto result = nr::modes(begin, end);
    for(size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i] == expected[i]);
    }
    std::cout << "Test passed: modes" << "\n";
}

void BasicStats_Scope_tests()
{
    {
        std::vector<double> data{1, 2, 3, 4, 5};
        double expected = 4;
        BasicStats_VectorScope_test(data, expected);
    }

    {
        std::vector<double> data{10, 3, 7, 1, 9};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double expected = 9;
        BasicStats_VectorScope_test(data, expected);
        BasicStats_NumericSampleScope_test(dataSample, expected);
        BasicStats_IteratorScope_test(data.begin(), data.end(), expected);
    }

    {
        std::vector<double> data;
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_VectorScope_test(data);
        BasicStats_ExceptionTrue_In_NumericSampleScope_test(dataSample);
        BasicStats_ExceptionTrue_In_IteratorScope_test(data.begin(), data.end());
    }
}

void BasicStats_VectorScope_test(const std::vector<double> &vec, double expected)
{
    auto result = nr::Scope(vec);
    assert(result == expected);
    std::cout << "Test passed: Scope" << "\n";
}

void BasicStats_NumericSampleScope_test(const nr::NumericSample<double>& ns, double expected)
{
    auto result = ns.Scope();
    assert(result == expected);
    std::cout << "Test passed: Scope" << "\n";
}

void BasicStats_IteratorScope_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected)
{
    auto result = nr::Scope(begin, end);
    assert(result == expected);
    std::cout << "Test passed: Scope" << "\n";
}

void BasicStats_ExceptionTrue_In_VectorScope_test(const std::vector<double>& vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::Scope(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Scope threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleScope_test(const nr::NumericSample<double>& ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.Scope();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Scope threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorScope_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::Scope(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Scope threw exception for empty input\n";
}

void BasicStats_InterquartileRange_tests()
{
    {
        std::vector<double> data = {9, 1, 8, 2, 7, 3, 6, 4, 5};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double expected = 5.0;
        double eps = nr::Moduls::DEFAULT_EPS;
        BasicStats_VectorInterquartileRange_test(data, expected, eps);
        BasicStats_NumericSampleInterquartileRange_test(dataSample, expected, eps);
        BasicStats_IteratorInterquartileRange_test(data.begin(), data.end(), expected, eps);
    }

    {
        std::vector<double> data;
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_VectorInterquartileRange_test(data);
        BasicStats_ExceptionTrue_In_NumericSampleInterquartileRange_test(dataSample);
        BasicStats_ExceptionTrue_In_IteratorInterquartileRange_test(data.begin(), data.end());
    }
}

void BasicStats_VectorInterquartileRange_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::interquartile_range(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Interquartile Range" << "\n";
}

void BasicStats_NumericSampleInterquartileRange_test(const nr::NumericSample<double> &ns, double expected, double eps)
{
    auto result = ns.interquartile_range();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Interquartile Range" << "\n";
}

void BasicStats_IteratorInterquartileRange_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::interquartile_range(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Interquartile Range" << "\n";
}

void BasicStats_ExceptionTrue_In_VectorInterquartileRange_test(const std::vector<double> &vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::interquartile_range(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Interquartile Range threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleInterquartileRange_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.interquartile_range();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Interquartile Range threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorInterquartileRange_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::interquartile_range(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Interquartile Range threw exception for empty input\n";
}

void BasicStats_MeanAbsoluteDeviation_tests()
{
    {
        // Test 1: Simple Dataset
        // Data: {2, 2, 3, 4, 14}, Mean = 5
        // Deviations: |2-5|=3, |2-5|=3, |3-5|=2, |4-5|=1, |14-5|=9
        // Sum of deviations: 18. MAD = 18 / 5 = 3.6
        std::vector<double> data = {2, 2, 3, 4, 14};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        double expected = 3.6;
        double eps = nr::Moduls::DEFAULT_EPSILON;
        BasicStats_VectorMeanAbsoluteDeviation_test(data, expected, eps);
        BasicStats_NumericSampleMeanAbsoluteDeviation_test(dataSample, expected, eps);
        BasicStats_IteratorMeanAbsoluteDeviation_test(data.begin(), data.end(), expected, eps);
    }

    {
        std::vector<double> data;
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_VectorMeanAbsoluteDeviation_test(data);
        BasicStats_ExceptionTrue_In_NumericSampleMeanAbsoluteDeviation_test(dataSample);
        BasicStats_ExceptionTrue_In_IteratorMeanAbsoluteDeviation_test(data.begin(), data.end());
    }
}

void BasicStats_VectorMeanAbsoluteDeviation_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::mean_absolute_deviation(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Mean Absolute Deviation" << "\n";
}

void BasicStats_NumericSampleMeanAbsoluteDeviation_test(const nr::NumericSample<double> &ns, double expected, double eps)
{
    auto result = ns.mean_absolute_deviation();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Mean Absolute Deviation" << "\n";
}

void BasicStats_IteratorMeanAbsoluteDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::mean_absolute_deviation(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Mean Absolute Deviation" << "\n";
}

void BasicStats_ExceptionTrue_In_VectorMeanAbsoluteDeviation_test(const std::vector<double> &vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::mean_absolute_deviation(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Mean Absolute Deviation threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleMeanAbsoluteDeviation_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.mean_absolute_deviation();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Mean Absolute Deviation threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorMeanAbsoluteDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin==end must be empty
    bool exception_thrown = false;
    try {
        nr::mean_absolute_deviation(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Mean Absolute Deviation threw exception for empty input\n";
}

void BasicStats_Dispersion_tests()
{
    {
        // Tests for nr::dispersion (population variance)
        std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        // mean = 3, variance = 2.0
        double expected = 2.0;
        double eps = nr::Moduls::DEFAULT_EPSILON;
        BasicStats_VectorDispersion_test(data, expected, eps);
        BasicStats_NumericSampleDispersion_test(dataSample, expected, eps);
        BasicStats_IteratorDispersion_test(data.begin(), data.end(), expected, eps);

        std::vector<double> data4 = {100.0, 107.0, 110.0, 113.0, 117.0, 121.0, 126.0, 129.0, 135.0, 138.0, 144.0, 148.0};
        // mean = 124.0, variance = 213.5
        expected = 213.5;
        eps = 1.0;
        nr::NumericSample<double> dataSample1(data4.begin(), data4.end());
        BasicStats_VectorDispersion_test(data4, expected, eps);
        BasicStats_NumericSampleDispersion_test(dataSample1, expected, eps);
        BasicStats_IteratorDispersion_test(data4.begin(), data4.end(), expected, eps);
    }

    {
        std::vector<double> data;
        nr::NumericSample<double> dataSample(data.begin(), data.end());
        BasicStats_ExceptionTrue_In_VectorDispersion_test(data);
        BasicStats_ExceptionTrue_In_NumericSampleDispersion_test(dataSample);
        BasicStats_ExceptionTrue_In_IteratorDispersion_test(data.begin(), data.end());
    }
}

void BasicStats_VectorDispersion_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::dispersion(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: dispersion" << "\n";
}

void BasicStats_NumericSampleDispersion_test(const nr::NumericSample<double> &ns, double expected, double eps)
{
    auto result = ns.dispersion();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: dispersion" << "\n";
}

void BasicStats_IteratorDispersion_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::dispersion(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: dispersion" << "\n";
}

void BasicStats_ExceptionTrue_In_VectorDispersion_test(const std::vector<double> &vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::dispersion(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Dispersion threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleDispersion_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.dispersion();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Dispersion threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorDispersion_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::dispersion(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Dispersion threw exception for empty input\n";    
}

void BasicStats_StandardDeviation_tests()
{
    {
        // Tests for nr::standard_deviation (population standard deviation)
        std::vector<double> s1 = {1.0, 2.0, 3.0, 4.0, 5.0};
        nr::NumericSample<double> dataSample(s1.begin(), s1.end());
        double expected = std::sqrt(2.0); // variance = 2.0 -> stddev = sqrt(2)
        double eps = nr::Moduls::DEFAULT_EPSILON;
        BasicStats_VectorStandardDeviation_test(s1, expected, eps);
        BasicStats_NumericSampleStandardDeviation_test(dataSample, expected, eps);
        BasicStats_IteratorStandardDeviation_test(s1.begin(), s1.end(), expected, eps);

        // Tests for nr::standard_deviation (population standard deviation)
        std::vector<double> s4 = {1.0, 2.0, 3.0, 4.0, 5.0, 13.0, 24.0, 10.0, 71.0};
        expected = std::sqrt(441.73);
        eps = nr::Moduls::DEFAULT_EPSILON;
        BasicStats_VectorStandardDeviation_test(s4, expected, eps);
        BasicStats_IteratorStandardDeviation_test(s4.begin(), s4.end(), expected, eps);

        // empty data should throw
        std::vector<double> empty_sd;
        nr::NumericSample<double> emptyDataSample(empty_sd.begin(), empty_sd.end());
        BasicStats_ExceptionTrue_In_VectorStandardDeviation_test(empty_sd);
        BasicStats_ExceptionTrue_In_NumericSampleStandardDeviation_test(emptyDataSample);
        BasicStats_ExceptionTrue_In_IteratorStandardDeviation_test(empty_sd.begin(), empty_sd.end());
    }
}

void BasicStats_VectorStandardDeviation_test(const std::vector<double> &vec, double expected, double eps)
{
    auto result = nr::standard_deviation(vec);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Standard Deviation" << "\n";
}

void BasicStats_NumericSampleStandardDeviation_test(const nr::NumericSample<double> &ns, double expected, double eps)
{
    auto result = ns.standard_deviation();
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Standard Deviation" << "\n";
}

void BasicStats_IteratorStandardDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps)
{
    auto result = nr::standard_deviation(begin, end);
    assert(nr::Moduls::almostEqual(result, expected, eps));
    std::cout << "Test passed: Standard Deviation" << "\n";
}

void BasicStats_ExceptionTrue_In_VectorStandardDeviation_test(const std::vector<double> &vec)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::standard_deviation(vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Standard Deviation threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleStandardDeviation_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.standard_deviation();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Standard Deviation threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_IteratorStandardDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end)
{
    // begin == end must be empty
    bool exception_thrown = false;
    try {
        nr::standard_deviation(begin, end);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: Standard Deviation threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleMedian_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.median();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: median threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_VectorArithmeticMean_test(const std::vector<double> &ns)
{
    // vec must be empty
    bool exception_thrown = false;
    try {
        nr::arithmetic_mean(ns.begin(), ns.end());
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: arithmetic mean threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericArithmeticMean_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.arithmetic_mean();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: arithmetic mean threw exception for empty input\n";
}

void BasicStats_ExceptionTrue_In_NumericSampleUpperQuartile_test(const nr::NumericSample<double> &ns)
{
    // ns must be empty
    bool exception_thrown = false;
    try {
        ns.upper_quartile();
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Test passed: upper quartile threw exception for empty input\n";
}


