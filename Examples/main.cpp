#include "DataModel/NumericSample.h"
#include "io/CsvDataLoader.h"
#include "stats/ProbabilitySampling.h"
#include "io/FileDataLoader.h"
#include "stats/NonProbabilitySampling.h"
#include "DataModel/CSVTable.h"
#include "stats/BasicStats.h"

#include<iostream>
#include<cassert>
#include<string>

int main()
{    
    //CSVDataLoader store("example.csv");

   /* {
        nr::CSVTable<std::string, double> csv;
        FileDataLoader file_loader;
        nr::NumericSample<double> dt(file_loader.load("numbers.txt"));
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;
    }
    */

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::NumericSample<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::ProbabilitySampling::systematic<double>(stats, sample);

        std::cout << "Systematic sample (" << sampleResult.size() << "):";
        for (double v : sampleResult) std::cout << ' ' << v;
        std::cout << '\n';
    }

    {
        std::cout << "[TEST] Stratified sampling (grouped by label)\n";
        std::vector<double> stats({10,11,12,13, 20,21,22,23,24, 30,31,32, 40,41,42,43,44,45});
        // labels: three strata (0,1,2) and one smaller stratum (3)
        std::vector<size_t> labels = {1,1,1,1, 0,0,0,0,0, 2,2,2, 3,3,3,3,3,3};
        size_t sampleSize = 8;

        auto strat = nr::ProbabilitySampling::stratified<double>(stats, labels, sampleSize);

        std::cout << "Stratified sample (" << strat.size() << "):";
        for (double v : strat) std::cout << ' ' << v;
        std::cout << '\n';
    }

    // --- CSVTable examples ---
    {
        std::cout << "[EXAMPLE] CSVTable: load from CSV file" << std::endl;
        const char* tmp_file = "example_tmp.csv";
        std::ofstream out(tmp_file);
        out << "Name,Age,Height\n";
        out << "Alice,25,1.65\n";
        out << "Bob,30,1.80\n";
        out << "Charlie,22,1.75\n";
        out << "Charlie, 22, 1.75\n";
        out.close();

        try {
            CSVDataLoader loader;
            nr::CSVTable table(&loader, std::string(tmp_file));

            std::cout << "Rows: " << table.row_count() << ", Cols: " << table.column_count() << std::endl;
            std::cout << "Has column 'Age': " << table.has_column("Age") << std::endl;
            std::cout << "Index of 'Height': " << table.column_index("Height") << std::endl;

            auto names = table.column("Name");
            std::cout << "Names:";
            for (const auto &n : names) std::cout << ' ' << n;
            std::cout << std::endl;

            // Extract typed columns
            auto ages = table.extract_column<int>("Age");
            auto heights = table.extract_column<double>("Height");
            std::cout << "Ages:";
            for (int a : ages) std::cout << ' ' << a;
            std::cout << std::endl;

            std::cout << "Heights:";
            for (double h : heights) std::cout << ' ' << h;
            std::cout << std::endl;

            // Apply basic statistics to extracted columns
            try {
                std::cout << "Age stats: min=" << nr::min(ages)
                          << " max=" << nr::max(ages)
                          << " mean=" << nr::arithmetic_mean(ages)
                          << " median=" << nr::median(ages)
                          << std::endl;

                std::cout << "Height stats: min=" << nr::min(heights)
                          << " max=" << nr::max(heights)
                          << " mean=" << nr::arithmetic_mean(heights)
                          << " median=" << nr::median(heights)
                          << std::endl;

                std::cout << "Age 25th percentile=" << nr::percentile(ages, 25.0)
                          << " 50th=" << nr::percentile(ages, 50.0)
                          << " 75th=" << nr::percentile(ages, 75.0)
                          << std::endl;

                auto maybe_mode = nr::mode(ages);
                if (maybe_mode) std::cout << "Age unique mode=" << *maybe_mode << std::endl;
                else std::cout << "Age unique mode: none" << std::endl;

                auto age_modes = nr::modes(ages);
                std::cout << "Age modes:";
                for (const auto &m : age_modes) std::cout << ' ' << m;
                std::cout << std::endl;
            }
            catch (const std::exception &e) {
                std::cerr << "Statistics failed: " << e.what() << std::endl;
            }

            // --- Example: extract a full row as strings and operate on it ---
            try {
                auto row0 = table.extract_row<std::string>(0); // first data row
                std::cout << "Row[0] cells:";
                for (const auto &cell : row0) std::cout << ' ' << cell;
                std::cout << std::endl;

                // Example string operations: join cells, length of name
                std::string joined;
                for (size_t i = 0; i < row0.size(); ++i) {
                    if (i) joined += ", ";
                    joined += row0[i];
                }
                std::cout << "Joined row: " << joined << std::endl;

                std::cout << "Name length: " << row0[0].size() << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Row extraction failed: " << e.what() << std::endl;
            }
        }
        catch (const std::exception &e) {
            std::cerr << "CSVTable example failed: " << e.what() << std::endl;
        }

        std::remove(tmp_file);
    }

    {
        std::cout << "[EXAMPLE] CSVTable: construct from headers and add rows" << std::endl;
        nr::CSVTable::row_type headers = {"X", "Y", "Label"};
        nr::CSVTable table(headers);
        table.add_row({"1", "2", "A"});
        table.add_row({"3", "4", "B"});

        std::cout << "Rows: " << table.row_count() << ", Cols: " << table.column_count() << std::endl;
        auto colX = table.column(0);
        std::cout << "Column X:";
        for (const auto &c : colX) std::cout << ' ' << c;
        std::cout << std::endl;
    }

    return 0;
}