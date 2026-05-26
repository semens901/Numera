#ifndef NUMERICSAMPLETESTS_H
#define NUMERICSAMPLETESTS_H
#include "Moduls/Moduls.h"
#include "DataModel/NumericSample.h"
#include <iostream>
#include <cassert>
#include <string>


void numeric_sample_tests();

void numeric_SizeToZero_test(const nr::NumericSample<double>& ns);
void numeric_AddElements_test(nr::NumericSample<double>& ns);
void numeric_ClearElements_test(nr::NumericSample<double>& ns);
void numeric_CopyAndMove_test();
void numeric_RemoveElements_test(nr::NumericSample<double> ns);

#endif // NUMERICSAMPLETESTS_H