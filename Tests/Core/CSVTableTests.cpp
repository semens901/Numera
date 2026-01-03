#include "CSVTableTests.h"

void csv_table_tests()
{
    
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
    nr::CSVTable table(loader, std::string(tmp_file));
    std::remove(tmp_file);

    assert(table.row_count() == 3);
    assert(table.column_count() == 3);
    assert(!table.empty());
    assert(table.has_column("Age"));
    assert(!table.has_column("Weight"));
    assert(table.column_index("Height") == 2);
    auto age_column = table.column("Age");
    assert(age_column.size() == 3);
    assert(age_column[0] == "25");
    assert(age_column[1] == "30");
    assert(age_column[2] == "22");

    // Tests for extract<T>
    auto ages = table.extract<int>("Age");
    assert(ages.size() == 3);
    assert(ages[0] == 25);
    assert(ages[1] == 30);
    assert(ages[2] == 22);

    auto heights = table.extract<double>("Height");
    assert(heights.size() == 3);
    assert(heights[0] == 1.65);
    assert(heights[1] == 1.80);
    assert(heights[2] == 1.75);

    auto names = table.extract<std::string>("Name");
    assert(names.size() == 3);
    assert(names[0] == "Alice");
    assert(names[1] == "Bob");
    assert(names[2] == "Charlie");
    
}
