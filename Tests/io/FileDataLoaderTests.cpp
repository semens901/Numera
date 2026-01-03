#include "FileDataLoaderTests.h"

void file_data_loader_tests()
{
    {
        const char* tmp_file = "tmp_test.txt";

        std::ofstream out(tmp_file);
        out << "1.2\n3.4\n5.6\n";
        out.close();

        std::cout << "[TEST] Open simple file\n";
        FileDataLoader file_loader;
        nr::NumericSample<double> dt(file_loader.load("tmp_test.txt"));
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;
        std::cout << "Test passed\n";
        std::remove(tmp_file);
    }
}
