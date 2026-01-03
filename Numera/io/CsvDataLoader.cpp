#include "CsvDataLoader.h"

std::unordered_map<std::string, std::vector<std::string>> CSVDataLoader::load(const std::string& filename)
{
    container_type result;
    column_order.clear();

    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + filename);

    std::string line;
    if (!std::getline(file, line)) return result; // пустой файл

    // Сохраняем заголовки и порядок
    column_order = split(line, ',');
    for (const auto& col : column_order) result[col] = {};

    // Чтение строк
    while (std::getline(file, line)) {
        auto values = split(line, ',');
        for (size_t i = 0; i < values.size() && i < column_order.size(); ++i) {
            result[column_order[i]].push_back(values[i]);
        }
    }

    m_data = result; // сохраняем внутрь класса, если нужно
    return result;
}

void CSVDataLoader::save(const std::string &filename, const std::unordered_map<std::string, std::vector<std::string>> &data) const
{
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file for writing: " + filename);

    // Пишем заголовки в порядке column_order
    for (size_t i = 0; i < column_order.size(); ++i) {
        file << column_order[i];
        if (i + 1 < column_order.size()) file << ",";
    }
    file << "\n";

    // Определяем количество строк (берём длину первой колонки)
    size_type n = 0;
    if (!column_order.empty()) n = data.at(column_order[0]).size();

    for (size_type row = 0; row < n; ++row) {
        for (size_t col = 0; col < column_order.size(); ++col) {
            file << data.at(column_order[col])[row];
            if (col + 1 < column_order.size()) file << ",";
        }
        file << "\n";
    }
}

const std::vector<std::string> &CSVDataLoader::get_column_order() const
{
    return column_order; 
}

std::vector<std::string> CSVDataLoader::split(const std::string &s, char delimiter) const
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(s);
    while (std::getline(ss, token, delimiter)) tokens.push_back(token);
    return tokens;
}
