#include "FileDataLoaderTests.h"

void file_data_loader_tests()
{
    file_data_FileRead_test();
}

void file_data_FileRead_test()
{
    const char* tmp_file = "tmp_test.txt";

        std::ofstream out(tmp_file);
        out << "1.2\n3.4\n5.6\n";
        out.close();

        std::cout << "[TEST] Open simple file\n";
        FileDataLoader file_loader;
        auto file = file_loader.load(tmp_file, '\n');
        nr::NumericSample<double> dt(file.begin(), file.end());
        std::cout << "Count:\t" << dt.size() << std::endl;
        std::cout << "Min:\t" << nr::min(dt) << std::endl;

        assert(dt.size() == 3);
        assert(nr::min(dt) == 1.2);

        std::cout << "Test passed\n";
        std::remove(tmp_file);
}
