project(range_experiments_benchmarks)

add_executable(benchmarks basic_bench.cpp)
target_link_libraries(benchmarks benchmark::benchmark)
