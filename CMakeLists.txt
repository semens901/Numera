cmake_minimum_required(VERSION 3.16)
project(Numera VERSION 0.0.1 LANGUAGES CXX)

# Setting the standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option for tests
option(NUMERA_ENABLE_TESTS "Enable building tests" ON)

# Adding a library
add_library(numera
    numera/Numera.cpp
)

target_include_directories(numera
    PUBLIC
        ${PROJECT_SOURCE_DIR}/numera
)

# Example of use
add_executable(numera_example
    examples/main.cpp
)

target_link_libraries(numera_example
    PRIVATE numera
)

# Tests
if(NUMERA_ENABLE_TESTS)
    add_executable(numera_tests
        tests/NumeraTests.cpp
    )
    target_link_libraries(numera_tests PRIVATE numera)
endif()

# Installation (optional)
install(TARGETS numera
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY numera/ DESTINATION include)
