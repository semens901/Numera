#ifndef CSVDATALOADER_H
#define CSVDATALOADER_H
#include "IDataLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

class CSVDataLoader : public IDataLoader<std::unordered_map<std::string, std::vector<std::string>>>{
public:
    CSVDataLoader(const std::string& filename)
        : m_filename(filename) {}
    CSVDataLoader() = default;
    /*
        This class can work with CSV files.
    */
    using value_type = std::string;
    using container_type = std::unordered_map<std::string, std::vector<std::string>>;
    using size_type = std::size_t;

    // Reading a CSV file
    container_type load(const std::string& filename) override;

    // Write to file
    void save(const std::string& filename, const std::unordered_map<std::string, std::vector<std::string>>& data) const override;
    const std::vector<std::string>& get_column_order() const;
private:
    value_type m_filename;
    container_type m_data;
    std::vector<std::string> column_order;

    // Helper function for splitting a string by a delimiter
    std::vector<std::string> split(const std::string& s, char delimiter) const;
};

#endif //CSVDATALOADER_H