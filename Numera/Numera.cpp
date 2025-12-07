#include "Numera.h"

nr::Numera::Numera(std::string filename, IDataLoader& loader)
{
    this->fileName = filename;
    load_data(fileName, loader);
    numbers = loader.load(fileName);
}

nr::Numera::Numera(std::vector<double> nums)  : numbers(nums) {}

nr::Numera::Numera(const Numera& other)
{
    this->numbers = other.numbers;
    this->fileName = other.fileName;
}

nr::Numera& nr::Numera::operator=(const Numera& other)
{
    if (this != &other)
    {
        this->numbers = other.numbers;
        this->fileName = other.fileName;
    }
    return *this;
}

nr::Numera::Numera()
{
}

nr::Numera::~Numera()
{
}

void nr::Numera::add(double number)
{
    numbers.push_back(number);
}

void nr::Numera::add(std::vector<double> nums)
{
    numbers.insert(numbers.end(), nums.begin(), nums.end());
} 

size_t nr::Numera::size() const
{
    return numbers.size();
}

double nr::Numera::min() const
{
    if (numbers.empty()) return 0.0;
    return *std::min_element(numbers.begin(), numbers.end());
}

double nr::Numera::max() const
{
    if (numbers.empty()) return 0.0;
    return *std::max_element(numbers.begin(), numbers.end());
}

double nr::Numera::mean() const
{
    if (numbers.empty()) return 0.0;
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum/numbers.size();
}

double nr::Numera::median() const
{
    if (numbers.empty()) return 0.0;
    std::vector<double> numbersCopy(numbers);
    std::sort(numbersCopy.begin(), numbersCopy.end());
    size_t size = numbersCopy.size();
    if(size % 2 == 1)
    {
        return numbersCopy[size / 2];
    }
    else
    {
        return (numbersCopy[size / 2 - 1] +
             numbersCopy[size / 2]) / 2.0;
    }
}

double nr::Numera::stddev() const
{
    if (numbers.empty()) return 0.0;
    const std::size_t n = numbers.size();
    if (n == 1) return 0.0;

    long double m = mean();
    long double sumSquaredDiffs = 0.0L;
    for (double x : numbers)
    {
        long double diff = (long double)x - m;
        sumSquaredDiffs += diff * diff;
    }

    // Use sample variance (Bessel's correction): divide by (n - 1)
    long double variance = sumSquaredDiffs / (long double)(n - 1);
    return std::sqrt((double)variance);
}
void nr::Numera::load_data(const std::string& fileName, IDataLoader& loader)
{
    numbers = loader.load(fileName);
}
void nr::Numera::save_data(const std::string& fileName, IDataLoader& loader) const
{
    loader.save(fileName, numbers);
}
/*
double nr::Numera::variance() const
{

    if (numbers.empty()) return 0.0;
    const std::size_t n = numbers.size();
    if (n == 1) return 0.0;

    long double m = mean();
    long double sumSquaredDiffs = 0.0L;
    for (double x : numbers)
    {
        long double diff = (long double)x - m;
        sumSquaredDiffs += diff * diff;
    }

    // Use sample variance (Bessel's correction): divide by (n - 1)
    long double variance = sumSquaredDiffs / (long double)(n - 1);
    return (double)variance;

}
*/

std::vector<double>::const_iterator nr::Numera::begin() const
{
    return numbers.begin();
}

std::vector<double>::const_iterator nr::Numera::end() const
{
    return numbers.end();
}

double nr::Numera::at(size_t index) const
{
    return 0.0;
}

double nr::Numera::front() const
{
    return 0.0;
}

double nr::Numera::back() const
{
    return 0.0;
}

void nr::Numera::clear()
{
    numbers.clear();
}

bool nr::Numera::empty() const
{
    return false;
}

void nr::Numera::pop_back()
{
}

void nr::Numera::remove_at(size_t index)
{
}
