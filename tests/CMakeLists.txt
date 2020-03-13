project(range_experiments_tests)

enable_testing()

include(FetchContent)

FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests basic_test.cpp)
target_link_libraries(unit_tests gtest_main)
add_test(unit_tests unit_tests)
