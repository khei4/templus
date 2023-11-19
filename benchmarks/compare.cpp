#include <benchmark/benchmark.h>
#include <string>

const std::string x =
    "hellooooooooooooooooooooooooooooooooooooooooooooooooooooo";
static void BM_StrCmp_Eq(benchmark::State &state) {
  for (auto _ : state)
    x.compare("hellooooooooooooooooooooooooooooooooooooooooooooooooooooo");
}
static void BM_StrCmp_Last(benchmark::State &state) {
  for (auto _ : state)
    x.compare("helloooooooooooooooooooooooooooooooooooooooooooooooooooob");
}

static void BM_StrCmp_Begin(benchmark::State &state) {
  for (auto _ : state)
    x.compare("gellooooooooooooooooooooooooooooooooooooooooooooooooooooo");
}

BENCHMARK(BM_StrCmp_Eq);
BENCHMARK(BM_StrCmp_Last);
BENCHMARK(BM_StrCmp_Begin);

BENCHMARK_MAIN();
