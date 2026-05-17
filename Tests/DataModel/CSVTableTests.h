#ifndef CSVTABLETESTS_H
#define CSVTABLETESTS_H
#include "DataModel/NumericSample.h"
#include "DataModel/CSVTable.h"
#include "io/CsvDataLoader.h"
#include "stats/ProbabilitySampling.h"
#include "stats/NonProbabilitySampling.h"
#include "stats/BasicStats.h"
#include "io/CsvDataLoader.h"

#include<iostream>
#include<cassert>
#include<string>
#include <sstream>

void csv_table_tests();

void CSVTable_ReadRowCount_test(const nr::CSVTable& table);
void CSVTable_ColumnCount_test(const nr::CSVTable& table);
void CSVTable_Empty_test(const nr::CSVTable& table);
void CSVTable_HasColumn_test(const nr::CSVTable& table);
void CSVTable_ColumnIndex_test(const nr::CSVTable& table);
void CSVTable_ColumnGet_test(const nr::CSVTable& table);
void CSVTable_ExtractIntColumn_test(const nr::CSVTable& table);
void CSVTable_ExtractDoubleColumn_test(const nr::CSVTable& table);
void CSVTable_ExtractStringColumn_test(const nr::CSVTable& table);


#endif // CSVTABLETESTS_H