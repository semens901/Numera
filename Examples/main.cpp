#include "Core/VectorData.h"
#include "io/CsvDataLoader.h"
#include "stats/Sampling.h"
#include "io/FileDataLoader.h"
#include "Core/CsvData.h"

#include<iostream>
#include<cassert>
#include<string>

int main()
{    
    CSVDataLoader store("example.csv");
    
    if (store.load().size() > 0) 
    {
        std::cout << "CSV-файл успешно прочитан!" << std::endl;
        store.print();

        // Пример: получить все значения колонки "Name"
        auto names = store.get("Name");
        std::cout << "Name column: ";
        for (const auto& n : names) std::cout << n << " ";
        std::cout << std::endl;
    } else 
    {
        std::cout << "Ошибка при чтении CSV-файла." << std::endl;
    }

    {
        nr::CSVDataStore<std::string, double> csv;
        FileDataLoader file_loader;
        nr::VectorData<double> dt(file_loader.load("numbers.txt"));
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;
    }

    {
        nr::CSVDataStore<std::string, double> csv(std::map<std::string, std::vector<double>>{{"hello", {1,2,3}},{"hi", {0,4,5}}});
        std::cout << "Min:\t" << "(" << csv.min() << ")" << std::endl; 
        std::cout << "Max:\t" << "(" << csv.max() << ")" << std::endl;
    }

    {
        std::cout << "[TEST] Simple random sampling\n";

        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sampleSize = 5;
        auto sample = nr::Sampling::simple_random(stats, sampleSize);

        assert(sample.size() == sampleSize);

        std::cout << "Simple random sample (" << sample.size() << "):";
        for (double v : sample) std::cout << ' ' << v;
        std::cout << '\n';

        nr::CSVDataStore<std::string, double> cd{std::map<std::string, std::vector<double>>
        {
            {"Test1", {1, 2, 5,3}},
            {"Test2", {0, 12, 14}},
            {"Test3", {15, 90, 84, 15}}
        }};

        std::vector<double> res = nr::Sampling::simple_random(cd, sampleSize);
        std::cout << "SAMPLE SIZE\t" << res.size();
        assert(res.size() == sampleSize);
    }

    {
        std::cout << "[TEST] Systematic sampling\n";
        nr::VectorData<double> stats({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 14, 11, 80, 15, 90});

        size_t sample = 4;
        auto sampleResult = nr::Sampling::systematic(stats, sample);

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

        auto strat = nr::Sampling::stratified(stats, labels, sampleSize);

        std::cout << "Stratified sample (" << strat.size() << "):";
        for (double v : strat) std::cout << ' ' << v;
        std::cout << '\n';
    }

    return 0;
}