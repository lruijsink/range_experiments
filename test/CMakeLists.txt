project(range_experiments_tests)

add_executable(unit_tests basic_test.cpp)
target_link_libraries(unit_tests gtest_main)
add_test(unit_tests unit_tests)
