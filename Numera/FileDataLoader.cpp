#include "FileDataLoader.h"

std::vector<double> FileDataLoader::load(const std::string& filename)
{
    std::vector<double> numbers;
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    
    double value;
    while (file >> value) 
    {
        numbers.push_back(value);
    }
    return numbers;
}

void FileDataLoader::save(const std::string& filename, const std::vector<double>& data) const
{
    std::ofstream output_file(filename);

    if (!output_file.is_open()) 
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (const double value : data) 
    {

        output_file << value << '\n';
    }

    output_file.close();
        
}
