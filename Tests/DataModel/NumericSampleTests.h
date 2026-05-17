#ifndef NUMERICSAMPLETESTS_H
#define NUMERICSAMPLETESTS_H
#include "DataModel/NumericSample.h"
#include <iostream>
#include <cassert>
#include <string>

bool almostEqual(double a, double b, double eps);
void numeric_sample_tests();

void numeric_SizeToZero_test(const nr::NumericSample<double>& ns);
void numeric_AddElements_test(nr::NumericSample<double>& ns);
void numeric_ClearElements_test(nr::NumericSample<double>& ns);
void numeric_CopyAndMove_test();
void numeric_RemoveElements_test(nr::NumericSample<double> ns);
void numeric_Min_test(const nr::NumericSample<double>& ns, double expected);
void numeric_Max_test(const nr::NumericSample<double>& ns, double expected);
void numeric_ArithmeticMean_test(const nr::NumericSample<double>& ns, double expected);
void numeric_WeightedMean_test(const nr::NumericSample<double>& ns, const std::vector<double>& weights, double expected);
void numeric_GeometricMean_test(const nr::NumericSample<double>& ns, const double expected, const double eps);
void numeric_GeometricMeanIntException_test(const nr::NumericSample<int>& ns);
void numeric_GeometricMeanDoubleException_test(const nr::NumericSample<double>& ns);


#endif // NUMERICSAMPLETESTS_H