#include <benchmark/benchmark.h>
#include "lt3/range/filter.h"

auto get_values(int64_t n)
{
  auto res = std::vector<int>(n);
  for (int i = 0; i < n; i++)
    res[i] = i;
  return res;
}

static void input_size_args(benchmark::internal::Benchmark* b) {
  b->Arg(0);
  for (int i = 0; i <= 10; ++i)
    b->Arg(1ll << (1 * i));
}

auto is_odd = [] (auto x) { return x / 2 == 1; };

static void bench_filter_view(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    for (auto v : values | lt3::range::filter(is_odd))
    {
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(bench_filter_view)->Apply(input_size_args);

static void bench_direct(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    for (auto v : values)
    {
      if (is_odd(v))
      {
        benchmark::ClobberMemory();
      }
    }
  }
}
BENCHMARK(bench_direct)->Apply(input_size_args);

static void bench_explicit(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    auto it = values.begin();
    while (it != values.end() && !is_odd(*it))
      it++;

    while (it != values.end())
    {
      it++;
      while (it != values.end() && !is_odd(*it))
        it++;

      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(bench_explicit)->Apply(input_size_args);

BENCHMARK_MAIN();
