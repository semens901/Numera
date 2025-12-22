cmake_minimum_required(VERSION 3.10)

# ---- Tests executable ----
add_executable(numera_tests
    NumeraTests.cpp

    # Core tests
    Core/VectorDataTests.cpp
    Core/CsvDataTests.cpp
    Core/JsonDataStoreTests.cpp

    # IO tests
    io/CsvDataLoaderTests.cpp
    io/FileDataLoaderTests.cpp
    io/JsonDataLoaderTests.cpp

    # Stats tests
    stats/BasicStatsTests.cpp
    stats/DescriptiveStatsTests.cpp
    stats/DistributionsTests.cpp
    stats/NonProbabilitySamplingTests.cpp
    stats/ProbabilitySamplingTests.cpp
)

target_link_libraries(numera_tests PRIVATE Numera)
target_compile_features(numera_tests PRIVATE cxx_std_17)

add_test(NAME numera_tests COMMAND numera_tests)
