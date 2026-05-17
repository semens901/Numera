#include "CSVTableTests.h"

void csv_table_tests()
{
    std::cout << "Running CSVTable tests..." << std::endl;
    std::string csv_content = 
        " Name,Age,Height\n"
        "Alice, 25,1.65\n"
        "Bob,30,1.80 \n"
        "Charlie ,22,1.75\n";

    const char* tmp_file = "tmp_test.txt";

    std::ofstream out(tmp_file);
    out << csv_content;
    out.close();

    CSVDataLoader loader;
    nr::CSVTable table(&loader, std::string(tmp_file), ',');
    std::remove(tmp_file);

    CSVTable_ReadRowCount_test(table);
    CSVTable_ColumnCount_test(table);
    CSVTable_Empty_test(table);
    CSVTable_HasColumn_test(table);
    CSVTable_ColumnIndex_test(table);
    CSVTable_ColumnGet_test(table);
    CSVTable_ExtractIntColumn_test(table);
    CSVTable_ExtractDoubleColumn_test(table);
    CSVTable_ExtractStringColumn_test(table);
    std::cout << "All CSVTable tests passed!" << std::endl;
}

void CSVTable_ReadRowCount_test(const nr::CSVTable &table)
{
    assert(table.row_count() == 3);
    std::cout << "CSVTable row count test passed! Row count: " << table.row_count() << std::endl;
}

void CSVTable_ColumnCount_test(const nr::CSVTable &table)
{
    assert(table.column_count() == 3);
    std::cout << "CSVTable column count test passed! Column count: " << table.column_count() << std::endl;
}

void CSVTable_Empty_test(const nr::CSVTable &table)
{
    assert(!table.empty());
    std::cout << "CSVTable empty test passed! Table is not empty." << std::endl;
}

void CSVTable_HasColumn_test(const nr::CSVTable &table)
{
    assert(table.has_column("Age"));
    assert(!table.has_column("Weight"));
    std::cout << "CSVTable has_column test passed! 'Age' exists, 'Weight' does not exist." << std::endl;
}

void CSVTable_ColumnIndex_test(const nr::CSVTable &table)
{
    assert(table.column_index("Age") == 1);
    assert(table.column_index("Height") == 2);
    std::cout << "CSVTable column index test passed!" << std::endl;
}

void CSVTable_ColumnGet_test(const nr::CSVTable &table)
{
    auto age_column = table.column("Age");
    assert(age_column.size() == 3);
    assert(age_column[0] == "25");
    assert(age_column[1] == "30");
    assert(age_column[2] == "22");
    std::cout << "CSVTable extract_column test passed! Extracted 'Age' column successfully." << std::endl;
}

void CSVTable_ExtractIntColumn_test(const nr::CSVTable &table)
{
    auto ages = table.extract_column<int>("Age");
    assert(ages.size() == 3);
    assert(ages[0] == 25);
    assert(ages[1] == 30);
    assert(ages[2] == 22);
    std::cout << "CSVTable extract_column<int> test passed! Extracted 'Age' column as integers successfully." << std::endl;
}

void CSVTable_ExtractDoubleColumn_test(const nr::CSVTable &table)
{
    auto heights = table.extract_column<double>("Height");
    assert(heights.size() == 3);
    assert(heights[0] == 1.65);
    assert(heights[1] == 1.80);
    assert(heights[2] == 1.75);
    std::cout << "CSVTable extract_column<double> test passed! Extracted 'Height' column as doubles successfully." << std::endl;
}

void CSVTable_ExtractStringColumn_test(const nr::CSVTable &table)
{
    auto names = table.extract_column<std::string>("Name");
    assert(names.size() == 3);
    assert(names[0] == "Alice");
    assert(names[1] == "Bob");
    assert(names[2] == "Charlie");
    std::cout << "CSVTable tests passed!" << std::endl;
}
