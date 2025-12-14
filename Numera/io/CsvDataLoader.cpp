#include "CsvDataLoader.h"

std::map<std::string, std::vector<std::string>> CSVDataLoader::load(const std::string& filename)
{
    char delimiter = ',';

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return {};
    }

    std::string line;
    
    // Считать заголовки (имена колонок)
    if (!std::getline(file, line)) return {};
    std::vector<std::string> headers = split(line, delimiter);

    // Инициализируем мапу пустыми векторами
    for (const auto& header : headers) {
        m_data[header] = {};
    }

    // Чтение данных
    while (std::getline(file, line)) {
        std::vector<std::string> row = split(line, delimiter);
        for (size_t i = 0; i < headers.size(); ++i) {
            if (i < row.size()) {
                m_data[headers[i]].push_back(row[i]);
            } else {
                m_data[headers[i]].push_back(""); // если данных меньше, чем колонок
            }
        }
    }

    file.close();
    return m_data;
}

void CSVDataLoader::save(const std::string &filename, const std::map<std::string, std::vector<std::string>> &data) const
{
    char delimiter = ',';
    std::ofstream file(filename);

    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    if (data.empty()) {
        return; // пустой CSV
    }

    // --- 1. Записываем заголовок ---
    {
        bool first = true;
        for (const auto& [column, _] : data) {
            if (!first) {
                file << delimiter;
            }
            file << column;
            first = false;
        }
        file << '\n';
    }

    // --- 2. Проверяем одинаковую длину столбцов ---
    const std::size_t row_count = data.begin()->second.size();

    for (const auto& [_, column_data] : data) {
        if (column_data.size() != row_count) {
            throw std::runtime_error("CSVDataLoader::save: columns have different sizes");
        }
    }

    // --- 3. Записываем строки ---
    for (std::size_t row = 0; row < row_count; ++row) {
        bool first = true;

        for (const auto& [_, column_data] : data) {
            if (!first) {
                file << delimiter;
            }
            file << column_data[row];
            first = false;
        }

        file << '\n';
    }
}

std::vector<std::string> CSVDataLoader::split(const std::string &s, char delimiter) const
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}
