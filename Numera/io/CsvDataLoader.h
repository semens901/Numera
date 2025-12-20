#include "IDataLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

class CSVDataLoader : public IDataLoader<std::map<std::string, std::vector<std::string>>>{
public:
    CSVDataLoader(const std::string& filename)
        : m_filename(filename) {}
    /*
        This class can work with CSV files.
    */
    using value_type = std::string;
    using container_type = std::map<std::string, std::vector<std::string>>;
    using size_type = std::size_t;

    // Reading a CSV file
    container_type load(const std::string& filename) override;

    // Write to file
    void save(const std::string& filename, const std::map<std::string, std::vector<std::string>>& data) const override;

private:
    value_type m_filename;    
    container_type m_data;

    // Helper function for splitting a string by a delimiter
    std::vector<std::string> split(const std::string& s, char delimiter) const;
};

