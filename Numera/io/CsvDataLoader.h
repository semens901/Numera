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

class CSVDataLoader final : public IDataLoader<std::unordered_map<std::string, std::vector<std::string>>>
{
public:
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
    // Helper function to trim whitespace from a string
    static std::string trim(const std::string& s);
};

#endif //CSVDATALOADER_H