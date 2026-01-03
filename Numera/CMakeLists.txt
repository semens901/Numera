cmake_minimum_required(VERSION 3.10)

# Library: numera
add_library(Numera STATIC

    Core/CSVTable.h
    Core/CSVTable.cpp
    Core/NumericSample.h

    io/CsvDataLoader.h
    io/CsvDataLoader.cpp
    io/FileDataLoader.h
    io/FileDataLoader.cpp
    io/IDataLoader.h
    io/json_reader.h
    io/json_writer.h
    io/FileDataLoader.cpp

    RandomGenerator/RandomValueGenerator.h
    RandomGenerator/RandomValueGenerator.cpp
    
    stats/BasicStats.h
    stats/Distributions.h
    stats/ProbabilitySampling.h
    stats/NonProbabilitySampling.h
)

target_include_directories(Numera
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(Numera PUBLIC cxx_std_17)
