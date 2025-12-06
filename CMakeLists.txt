cmake_minimum_required(VERSION 3.10)

project(Numera VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

# Add subprojects
add_subdirectory(numera)
add_subdirectory(examples)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
