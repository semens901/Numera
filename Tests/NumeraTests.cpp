#include "Core/CSVTableTests.h"
#include "Core/NumericSampleTests.h"
#include "io/CsvDataLoaderTests.h"
#include "io/FileDataLoaderTests.h"
#include "stats/BasicStatsTests.h"
#include "stats/NonProbabilitySamplingTests.h"
#include "stats/ProbabilitySamplingTests.h"

int main()
{
    basic_stats_tests();
    csv_table_tests();
    numeric_sample_tests();
    csv_data_loader();
    file_data_loader_tests();    
    non_probability_sampling_tests();
    probability_sampling_tests();

    return 0;
}