project(range_experiments_tests)

enable_testing()

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests basic_test.cpp)
target_link_libraries(unit_tests gtest_main)
add_test(unit_tests unit_tests)
