#include <benchmark/benchmark.h>

static void BM_SomeFunction(benchmark::State& state) {

  for (auto _ : state) {
    int x = 0;
  }
}
BENCHMARK(BM_SomeFunction);
BENCHMARK_MAIN();
