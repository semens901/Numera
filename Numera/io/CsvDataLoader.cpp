#include "CsvDataLoader.h"

/*
    Loads a CSV file into an unordered_map while preserving column order
    - First line is treated as a header
    - Leading and trailing whitespaces are trimmed
    - Column values preserve row order
    - Throws std::runtime_error if the file cannot be opened
*/

std::unordered_map<std::string, std::vector<std::string>>
CSVDataLoader::load(const std::string& filename)
{
    container_type result;
    column_order.clear();

    // Open CSV file
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filename);

    std::string line;

    // Read header line
    if (!std::getline(file, line))
        return result; // empty file

    // Parse and store column names (preserve order)
    column_order = split(line, ',');
    for (auto& col : column_order) {
        col = trim(col);
        result[col] = {};
    }

    // Read data rows
    while (std::getline(file, line)) {
        auto values = split(line, ',');
        for (size_t i = 0; i < values.size() && i < column_order.size(); ++i) {
            result[column_order[i]].push_back(trim(values[i]));
        }
    }

    m_data = result;
    return result;
}

void CSVDataLoader::save(const std::string &filename, const std::unordered_map<std::string, std::vector<std::string>> &data) const
{
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file for writing: " + filename);

    // Write header
    for (size_t i = 0; i < column_order.size(); ++i) {
        file << column_order[i];
        if (i + 1 < column_order.size()) file << ",";
    }
    file << "\n";

    // Determine the number of rows (take the length of the first column)
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
    /*
        Splits a string by the given delimiter and returns a vector of tokens.
        - Example: split("a,b,c", ',') → ["a", "b", "c"]
        - Note: This is a simple split that does not handle quoted delimiters or escaped characters.
    */
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(s);
    while (std::getline(ss, token, delimiter)) tokens.push_back(token);
    return tokens;
}

std::string CSVDataLoader::trim(const std::string &s)
{
    /*
        Trims leading and trailing whitespace from a string.
        - Example: trim("  hello ") → "hello"
        - Note: This function considers spaces, tabs, carriage returns, and newlines as whitespace
    */
    const auto first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";

    const auto last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}
