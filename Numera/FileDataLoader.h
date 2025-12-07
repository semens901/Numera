#ifndef NUMERA_FILEDATALOADER_H
#define NUMERA_FILEDATALOADER_H
#include "IDataLoader.h"

#include<fstream>
#include<vector>
#include<string>

class FileDataLoader : public IDataLoader 
{
public:
    std::vector<double> load(const std::string& filename) override;

    void save(const std::string& filename, const std::vector<double>& data) const override;
};

#endif // NUMERA_FILEDATALOADER_H