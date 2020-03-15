#include <benchmark/benchmark.h>
#include "lt3/range/filter.h"
#include "lt3/range/pure_lambdas.h"

auto get_values(int64_t n)
{
  auto res = std::vector<int>(n);
  for (int i = 0; i < n; i++)
    res[i] = i;
  return res;
}

static void input_size_args(benchmark::internal::Benchmark* b) {
  b->Arg(0);
  b->Arg(1);
  b->Arg(1 << 2);
  b->Arg(1 << 3);
  b->Arg(1 << 4);
  b->Arg(1 << 7);
  b->Arg(1 << 10);
  b->Arg(1 << 15);
  b->Arg(1 << 20);
}

auto is_odd = [] (auto x) { return x % 2 == 1; };

static void bench_filter_view(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    long sum = 0;
    for (auto v : values | lt3::range::filter(is_odd))
    {
      sum += v;
    }
    benchmark::DoNotOptimize(sum);
  }
}

static void bench_pure_lambdas(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    long sum = 0;
    for (auto v : values | lt3::range::pure_lambdas::filter(is_odd))
    {
      sum += v;
    }
    benchmark::DoNotOptimize(sum);
  }
}

static void bench_direct(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    long sum = 0;
    for (auto v : values)
    {
      if (is_odd(v))
      {
        sum += v;
      }
    }
    benchmark::DoNotOptimize(sum);
  }
}

static void bench_explicit(benchmark::State& state)
{
  auto values = get_values(state.range(0));
  for (auto _ : state)
  {
    long sum = 0;

    auto it = values.begin();
    while (it != values.end() && !is_odd(*it))
      it++;

    while (it != values.end())
    {
      sum += *it;

      it++;
      while (it != values.end() && !is_odd(*it))
        it++;
    }
    benchmark::DoNotOptimize(sum);
  }
}

BENCHMARK(bench_filter_view)->Apply(input_size_args);
BENCHMARK(bench_pure_lambdas)->Apply(input_size_args);
BENCHMARK(bench_direct)->Apply(input_size_args);
BENCHMARK(bench_explicit)->Apply(input_size_args);

BENCHMARK_MAIN();
