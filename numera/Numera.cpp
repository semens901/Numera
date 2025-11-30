#include "Numera.h"

nr::Numera::Numera(std::string fileName) : fileName(fileName)
{
    open_file(this->fileName);
    if(!is_open())
    {
        std::cerr << "Failed to open file!\n";
    }
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

size_t nr::Numera::count() const
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
bool nr::Numera::is_open() const
{
    return file.is_open();
}

void nr::Numera::open_file(std::string)
{
    file.open(fileName);
    if(is_open())
    {
        double i;
        while(file >> i)
        {
            numbers.push_back(i);
        }
    }
}
