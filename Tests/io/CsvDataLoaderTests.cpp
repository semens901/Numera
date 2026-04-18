#include "CsvDataLoaderTests.h"

void csv_data_loader()
{
    std::cout << "Running CSVDataLoader tests..." << std::endl;
    std::string csv_content = 
        "Name,Age,Height\n"
        "Alice,25,1.65\n"
        "Bob,30,1.80\n"
        "Charlie,22,1.75\n";

    const char* tmp_file = "tmp_test.txt";

    std::ofstream out(tmp_file);
    out << csv_content;
    out.close();

    CSVDataLoader loader;
    nr::CSVTable table(&loader, std::string(tmp_file));
    std::remove(tmp_file);

    assert(table.row_count() == 3);
    assert(table.column_count() == 3);

    std::cout << "Test passed: row count is " << table.row_count() << ", column count is " << table.column_count() << "\n";
}
