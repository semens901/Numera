#include "IDataLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

class CSVDataLoader : public IDataLoader<std::map<std::string, std::vector<std::string>>>{
public:
    CSVDataLoader(const std::string& filename, char delimiter = ',')
        : m_filename(filename), m_delimiter(delimiter) {}
    /*
        This class can work with CSV files.
    */
    using value_type = std::string;
    using container_type = std::map<std::string, std::vector<std::string>>;
    using size_type = std::size_t;

    // Reading a CSV file
    container_type load(const std::string& filename) override;
    container_type load();

    // Write to file
    void save(const std::string& filename, const std::map<std::string, std::vector<std::string>>& data) const override;
    // Get all values ​​by key (column)
    const std::vector<std::string>& get(const std::string& key) const;

    // Output all contents
    void print() const;

private:
    value_type m_filename;
    char m_delimiter;
    container_type m_data;

    // Вспомогательная функция для разделения строки по разделителю
    std::vector<std::string> split(const std::string& s, char delimiter) const;
};

