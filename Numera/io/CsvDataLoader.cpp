#include "CsvDataLoader.h"

bool CSVDataStore::read()
{
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << m_filename << std::endl;
        return false;
    }

    std::string line;
    
    // Считать заголовки (имена колонок)
    if (!std::getline(file, line)) return false;
    std::vector<std::string> headers = split(line, m_delimiter);

    // Инициализируем мапу пустыми векторами
    for (const auto& header : headers) {
        m_data[header] = {};
    }

    // Чтение данных
    while (std::getline(file, line)) {
        std::vector<std::string> row = split(line, m_delimiter);
        for (size_t i = 0; i < headers.size(); ++i) {
            if (i < row.size()) {
                m_data[headers[i]].push_back(row[i]);
            } else {
                m_data[headers[i]].push_back(""); // если данных меньше, чем колонок
            }
        }
    }

    file.close();
    return true;
}

const std::vector<std::string> &CSVDataStore::get(const std::string &key) const
{
    static const std::vector<std::string> empty;
    auto it = m_data.find(key);
    return it != m_data.end() ? it->second : empty;
}

void CSVDataStore::print() const
{
    for (const auto& [key, values] : m_data) {
        std::cout << key << " -> ";
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << values[i];
            if (i != values.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> CSVDataStore::split(const std::string &s, char delimiter) const
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}
