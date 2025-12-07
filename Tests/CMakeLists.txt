cmake_minimum_required(VERSION 3.10)

# Tests executable
add_executable(numera_tests
    NumeraTests.cpp
)

target_link_libraries(numera_tests PRIVATE Numera)
target_compile_features(numera_tests PRIVATE cxx_std_17)

add_test(NAME numera_tests COMMAND numera_tests)
