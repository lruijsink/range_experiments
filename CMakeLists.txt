cmake_minimum_required(VERSION 3.1.0)

project(range_experiments)

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git)
    
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git)
    
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(
    googletest
    googlebenchmark)
    
enable_testing()

include_directories(include)

add_subdirectory(test)
add_subdirectory(example)
add_subdirectory(bench)
