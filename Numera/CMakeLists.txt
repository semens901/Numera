cmake_minimum_required(VERSION 3.10)

# Library: numera
add_library(Numera STATIC
    Numera.cpp
    FileDataLoader.cpp
    RandomValueGenerator.cpp
    Sampling/Sampling.cpp
)

target_include_directories(Numera
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(Numera PUBLIC cxx_std_17)
