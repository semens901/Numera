#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H
#include<random>
#include<chrono>

namespace nr
{

    /*
        A class for generating random values using a thread-local Mersenne Twister 64-bit generator.
         - The generator is seeded with a combination of the current time and the thread ID to ensure different sequences across threads.
         - Provides a static method to access the thread-local generator instance.
         - This design allows for efficient and thread-safe random number generation without the overhead of locking.
    */

    class RandomValueGenerator
    {
        public:
            RandomValueGenerator() = delete;
            RandomValueGenerator(const RandomValueGenerator&) = delete;
            RandomValueGenerator& operator=(const RandomValueGenerator&) = delete;

            static std::mt19937_64& get_thread_local_generator();
    };
}
#endif // RANDOM_VALUE_GENERATOR_H