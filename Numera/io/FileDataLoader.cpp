#include "FileDataLoader.h"

std::vector<double> FileDataLoader::load(const std::string& filename)
{
    char delimiter = ',';
    std::vector<double> numbers;
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string token;
    while (std::getline(file, token, delimiter)) {
        if (token.empty()) continue;

        try {
            numbers.push_back(std::stod(token));
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid number: " + token);
        }
    }

    return numbers;
}

void FileDataLoader::save(const std::string& filename, const std::vector<double>& data) const
{
    char delimiter = ',';
    std::ofstream output_file(filename);

    if (!output_file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (std::size_t i = 0; i < data.size(); ++i) {
        output_file << data[i];
        if (i + 1 < data.size()) {
            output_file << delimiter;
        }
    }
}
