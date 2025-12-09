#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

class CSVDataStore {
public:
    CSVDataStore(const std::string& filename, char delimiter = ',')
        : m_filename(filename), m_delimiter(delimiter) {}

    // Чтение CSV-файла
    bool read();

    // Получить все значения по ключу (колонке)
    const std::vector<std::string>& get(const std::string& key) const;

    // Вывести всё содержимое
    void print() const;

private:
    std::string m_filename;
    char m_delimiter;
    std::map<std::string, std::vector<std::string>> m_data;

    // Вспомогательная функция для разделения строки по разделителю
    std::vector<std::string> split(const std::string& s, char delimiter) const;
};

