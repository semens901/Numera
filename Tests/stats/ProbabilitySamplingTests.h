#ifndef PROBABILITYSAMPLING_H
#define PROBABILITYSAMPLING_H
#include "DataModel/NumericSample.h"
#include "io/CsvDataLoader.h"
#include "stats/ProbabilitySampling.h"
#include "stats/NonProbabilitySampling.h"
#include "stats/BasicStats.h"
#include "io/FileDataLoader.h"

#include<iostream>
#include<cassert>
#include<string>

void probability_sampling_tests();

void ProbabilitySampling_SimpleRandom_tests();
void ProbabilitySampling_ContainerSimpleRandom_test();
void ProbabilitySampling_IteratorSimpleRandom_test();

void ProbabilitySampling_Systematic_tests();
void ProbabilitySampling_ContainerSystematic_test();
void ProbabilitySampling_IteratorSystematic_test();

void ProbabilitySampling_Stratified_tests();
void ProbabilitySampling_ContainerStratified_test();
void ProbabilitySampling_IteratorStratified_test();

#endif //PROBABILITYSAMPLING_H