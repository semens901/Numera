#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H
#include<random>
#include<chrono>

namespace nr
{
    class RandomValueGenerator
    {
        public:
            static std::mt19937_64& get_thread_local_generator();
    };
}
#endif // RANDOM_VALUE_GENERATOR_H