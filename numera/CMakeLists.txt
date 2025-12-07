cmake_minimum_required(VERSION 3.10)

# Library: numera
add_library(numera STATIC
    numera.cpp
    randomValueGenerator.cpp
    sampling/sampling.cpp
)

target_include_directories(numera
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(numera PUBLIC cxx_std_17)
