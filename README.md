# Numera

Numera is a compact C++20 library for working with statistical data, sampling methods, and lightweight data-loading utilities.

It is designed for applications that need fast access to descriptive statistics, simple probabilistic sampling techniques, and basic table/file processing without introducing heavy dependencies.

## Why Numera?

Numera combines several practical building blocks for data analysis:

- Descriptive statistics such as minimum, maximum, mean, median, quartiles, percentiles, modes, range, interquartile range, and mean absolute deviation
- Probability sampling methods including simple random, systematic, and stratified sampling
- Data containers and helpers for numeric samples and tabular data
- CSV and file-based loading utilities, with support for JSON-oriented helpers
- A modern CMake-based build system and C++20 support

## Key Features

### Statistics
Numera provides a rich set of reusable statistical functions for numeric containers and iterators:

- Minimum and maximum
- Arithmetic, geometric, and harmonic means
- Median and weighted mean
- Quartiles and percentiles
- Mode and multimodal support
- Range, interquartile range, and mean absolute deviation

### Sampling
The library includes common sampling strategies for survey and data analysis workflows:

- Simple random sampling
- Systematic sampling
- Stratified sampling

### Data handling
Numera also includes helpers for handling tabular and file-based data:

- Numeric sample container
- CSV table abstraction
- CSV/file loaders
- JSON reader and writer helpers

## Project Structure

- [Numera/DataModel](Numera/DataModel) — data structures such as numeric samples and table models
- [Numera/io](Numera/io) — loaders and serialization helpers
- [Numera/RandomGenerator](Numera/RandomGenerator) — random generation utilities
- [Numera/stats](Numera/stats) — statistics and sampling implementations
- [Examples](Examples) — example usage
- [Tests](Tests) — unit tests for core functionality

## Build and Run

Requirements:

- CMake 3.10 or newer
- A C++20-compatible compiler

Build the project:

```bash
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build
```

Run the example executable:

```bash
./build/Examples/numera_example
```

Run tests:

```bash
ctest --test-dir build --output-on-failure
```

## Quick Example

```cpp
#include <iostream>
#include "stats/BasicStats.h"
#include "stats/ProbabilitySampling.h"
#include "DataModel/NumericSample.h"

int main()
{
    nr::NumericSample<double> data({10, 20, 30, 40, 50});

    std::cout << "Mean: " << nr::arithmetic_mean(data) << '\n';
    std::cout << "Median: " << nr::median(data) << '\n';

    auto sample = nr::ProbabilitySampling::simple_random(data, 3);
    std::cout << "Sample size: " << sample.size() << '\n';
}
```

## License

This project is distributed under the MIT License. See the [LICENSE](LICENSE) file for details.
