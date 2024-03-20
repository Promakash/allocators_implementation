cmake_minimum_required(VERSION 3.28)
project(show_of_allocators)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wold-style-cast
        -Wconversion
        -Weffc++
)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(vendor/benchmark)

add_executable(bench_tests benchmarks.cpp)
target_compile_options(bench_tests
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wold-style-cast
        -Wconversion
        -Weffc++
)
target_link_libraries(bench_tests
        PUBLIC
        benchmark::benchmark_main
)