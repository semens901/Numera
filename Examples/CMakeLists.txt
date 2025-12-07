cmake_minimum_required(VERSION 3.10)

# Example executable that links to the numera library
add_executable(numera_example
    main.cpp
)

target_link_libraries(numera_example PRIVATE Numera)
target_compile_features(numera_example PRIVATE cxx_std_17)
