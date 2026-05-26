#ifndef BASICSTATSTESTS_H
#define BASICSTATSTESTS_H
#include "Moduls/Moduls.h"
#include "DataModel/NumericSample.h"
#include "DataModel/CSVTable.h"
#include "io/CsvDataLoader.h"
#include "stats/NonProbabilitySampling.h"
#include "stats/BasicStats.h"
#include "io/FileDataLoader.h"

#include<iostream>
#include<cassert>
#include<string>
#include<list>


void basic_stats_tests();

/* Min */
void BasicStats_Min_test(const nr::NumericSample<double>& ns, double expected);
void BasicStats_ExceptionTrue_In_Min_test(const nr::NumericSample<double>& ns);

/* Max */
void BasicStats_Max_test(const nr::NumericSample<double>& ns, double expected);
void BasicStats_ExceptionTrue_In_Max_test(const nr::NumericSample<double>& ns);

/* Weighted Mean */
void BasicStats_VectorWeightedMean_test(const std::vector<double>& vec, const std::vector<double>& weights, double expected);
void BasicStats_NumericSampleWeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights, double expected);
void BasicStats_IteratorWeightedMean_test(std::vector<double>::iterator begin_data, std::vector<double>::iterator end_data, std::vector<double>::iterator begin_weights, std::vector<double>::iterator end_weights, double expected);
void BasicStats_IteratorWithNoWeightedEndWeightedMean_test(std::vector<double>::iterator begin_data, std::vector<double>::iterator end_data, std::vector<double>::iterator begin_weights, double expected);
void BasicStats_ExceptionTrue_In_VectorWeightedMean_test(const std::vector<double>& vec, const std::vector<double>& weights);
void BasicStats_ExceptionTrue_In_NumericSampleWeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights);
void BasicStats_ExceptionTrue_In_IteratorWeightedMean_test(std::vector<double>::iterator beginData, std::vector<double>::iterator endData, std::vector<double>::iterator beginWeights, std::vector<double>::iterator endWeights);

/* Geometric Mean */
void BasicStats_VectorGeometricMean_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleGeometricMean_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorGeometricMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorGeometricMean_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericGeometricMean_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorGeometricMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

/* Harmonic Mean */
void BasicStats_VectorHarmonicMean_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleHarmonicMean_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorHarmonicMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorHarmonicMean_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericHarmonicMean_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorHarmonicMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

/* Lower Quartile */
void BasicStats_VectorLowerQuartile_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleLowerQuartile_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorLowerQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorLowerQuartile_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleLowerQuartile_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorLowerQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

/* Upper Quartile */
void BasicStats_VectorUpperQuartile_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleUpperQuartile_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorUpperQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorUpperQuartile_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleUpperQuartile_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorUpperQuartile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

/* Arithmetic Mean */
void BasicStats_VectorArithmeticMean_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleArithmeticMean_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorArithmeticMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorArithmeticMean_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericArithmeticMean_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorArithmeticMean_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

/* Median */
void BasicStats_VectorMedian_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleMedian_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorMedian_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorMedian_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleMedian_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorMedian_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorPercentile_test(const std::vector<double>& vec, double p, double expected, double eps);
void BasicStats_NumericSamplePercentile_test(const nr::NumericSample<double>& ns, double p, double expected, double eps);
void BasicStats_IteratorPercentile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double p, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorPercentile_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSamplePercentile_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorPercentile_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorMode_test(const std::vector<double>& vec, double expected);
void BasicStats_NumericSampleMode_test(const nr::NumericSample<double>& ns, double expected);
void BasicStats_IteratorMode_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected);
void BasicStats_VectorModeHasValueFalse_test(const std::vector<double>& vec);
void BasicStats_NumericSampleModeHasValueFalse_test(const nr::NumericSample<double>& ns);
void BasicStats_IteratorModeHasValueFalse_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorModes_test(const std::vector<double>& vec, const std::vector<double>& expected);
void BasicStats_NumericSampleModes_test(const nr::NumericSample<double>& ns, const std::vector<double>& expected);
void BasicStats_IteratorModes_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, std::vector<double> expected);

void BasicStats_VectorScope_test(const std::vector<double>& vec, double expected);
void BasicStats_NumericSampleScope_test(const nr::NumericSample<double>& ns, double expected);
void BasicStats_IteratorScope_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected);
void BasicStats_ExceptionTrue_In_VectorScope_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleScope_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorScope_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorInterquartileRange_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleInterquartileRange_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorInterquartileRange_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorInterquartileRange_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleInterquartileRange_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorInterquartileRange_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorMeanAbsoluteDeviation_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleMeanAbsoluteDeviation_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorMeanAbsoluteDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorMeanAbsoluteDeviation_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleMeanAbsoluteDeviation_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorMeanAbsoluteDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorDispersion_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleDispersion_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorDispersion_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);
void BasicStats_ExceptionTrue_In_VectorDispersion_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleDispersion_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorDispersion_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

void BasicStats_VectorStandardDeviation_test(const std::vector<double>& vec, double expected, double eps);
void BasicStats_NumericSampleStandardDeviation_test(const nr::NumericSample<double>& ns, double expected, double eps);
void BasicStats_IteratorStandardDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end, double expected, double eps);


void BasicStats_ExceptionTrue_In_VectorStandardDeviation_test(const std::vector<double>& vec);
void BasicStats_ExceptionTrue_In_NumericSampleStandardDeviation_test(const nr::NumericSample<double>& ns);
void BasicStats_ExceptionTrue_In_IteratorStandardDeviation_test(std::vector<double>::iterator begin, std::vector<double>::iterator end);

#endif // BASICSTATSTESTS_H