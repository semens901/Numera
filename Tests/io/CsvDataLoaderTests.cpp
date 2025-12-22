#include "CsvDataLoaderTests.h"

void csv_data_loader()
{
    {
        const char* tmp_file = "tmp_test.txt";

        std::ofstream out(tmp_file);
        out << "QuotaAmount,StartDate,OwnerName,Username\n150000,2016-01-01,Chris Riley,trailhead9.ub20k5i9t8ou@example.com\n150000,2016-02-01,Chris Riley,trailhead9.ub20k5i9t8ou@example.com\n150000,2016-03-01,Chris Riley,trailhead9.ub20k5i9t8ou@example.com\n";
        out.close();
        std::cout << "[TEST] Open CSV file\n";
        CSVDataLoader store("tmp_test.txt");
    
        
        std::cout << "Test passed\n";
        std::remove(tmp_file);
    }
}
