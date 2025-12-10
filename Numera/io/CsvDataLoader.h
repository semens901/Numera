#include "IDataLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

class CSVDataStore : public IDataLoader<std::map<std::string, std::vector<std::string>>>{
public:
    CSVDataStore(const std::string& filename, char delimiter = ',')
        : m_filename(filename), m_delimiter(delimiter) {}

    using value_type = std::string;
    using container_type = std::map<std::string, std::vector<std::string>>;
    using size_type = std::size_t;

    // Чтение CSV-файла
    container_type load(const std::string& filename) override;
    container_type load();

    void save(const std::string& filename, const std::map<std::string, std::vector<std::string>>& data) const override;
    // Получить все значения по ключу (колонке)
    const std::vector<std::string>& get(const std::string& key) const;

    // Вывести всё содержимое
    void print() const;

private:
    value_type m_filename;
    char m_delimiter;
    container_type m_data;

    // Вспомогательная функция для разделения строки по разделителю
    std::vector<std::string> split(const std::string& s, char delimiter) const;
};

