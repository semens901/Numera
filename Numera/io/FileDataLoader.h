#ifndef NUMERA_FILEDATALOADER_H
#define NUMERA_FILEDATALOADER_H
#include "IDataLoader.h"

#include<fstream>
#include<vector>
#include<string>

class FileDataLoader : public IDataLoader<std::vector<double>>
{
public:
    /*
    This class can work with simple files in which data is written in the format
    21.1
    17.0
    15.5
    ...
    */
    using value_type = double;
    using container_type = std::vector<double>;
    using size_type = std::size_t;

    //Reading a file
    std::vector<double> load(const std::string& filename) override;

    //Writing to a file
    void save(const std::string& filename, const std::vector<double>& data) const override;
};

#endif // NUMERA_FILEDATALOADER_H