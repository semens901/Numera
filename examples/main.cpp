#include<iostream>
#include "Numera.h"

int main()
{
    nr::Numera nm("numbers.txt");
    if(!nm.is_open())
        return 1;
    std::cout << "Count:\t" << nm.count() << std::endl;
    std:: cout << "Min:\t" << nm.min() << std::endl;
    std:: cout << "Max:\t" << nm.max() << std::endl;
    std:: cout << "Arithmetic mean:\t" << nm.mean() << std::endl;
    std:: cout << "Median:\t" << nm.median() << std::endl;
    std:: cout << "Standard deviation:\t" << nm.stddev() << std::endl;
    return 0;
}