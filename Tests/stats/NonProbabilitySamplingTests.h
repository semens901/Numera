#ifndef NONPROBABILITYSAMPLING_H
#define NONPROBABILITYSAMPLING_H
#include "DataModel/NumericSample.h"
#include "io/CsvDataLoader.h"
#include "stats/NonProbabilitySampling.h"
#include "stats/BasicStats.h"
#include "io/FileDataLoader.h"

#include<iostream>
#include<cassert>
#include<string>

void non_probability_sampling_tests();


void NonProbabilitySampling_QuotaSampling_tests();
void NonProbabilitySampling_ContainerQuotaSampling_test();
void NonProbabilitySampling_IteratorQuotaSampling_test();

void NonProbabilitySampling_HaphazardSampling_tests();
void NonProbabilitySampling_ContainerHaphazardSampling_test();
void NonProbabilitySampling_IteratorHaphazardSampling_test();

void NonProbabilitySampling_ConvenienceSampling_tests();
void NonProbabilitySampling_ContainerConvenienceSampling_test();
void NonProbabilitySampling_IteratorConvenienceSampling_test();

//void NonProbabilitySampling_NumericQuotaSampling_test();


#endif //NONPROBABILITYSAMPLING_H