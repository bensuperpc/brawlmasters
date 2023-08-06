#include <string>
#include <iostream>

#include <benchmark/benchmark.h>

static void DoSetup(const benchmark::State& state) {
}

static void DoTeardown(const benchmark::State& state) {
}

template<typename T>
static void BasicBench(benchmark::State& state) {
  const auto range = state.range(0);
  std::string str;
  benchmark::DoNotOptimize(str);

  for (auto _ : state) {
    str = std::to_string(range);
    benchmark::ClobberMemory();
    //state.PauseTiming();
    //state.SkipWithError("No path found");
    //state.ResumeTiming();
  }
  // state.counters["range"] = range;
  state.SetItemsProcessed(state.iterations() * range * range);
  state.SetBytesProcessed(state.iterations() * range * range * sizeof(uint64_t));
}
BENCHMARK(BasicBench<uint64_t>)
    ->Name("BasicBench")
    ->RangeMultiplier(4)
    ->Range(16, 256)
    ->ThreadRange(1, 1)
    ->Unit(benchmark::kNanosecond)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown)
    ->MeasureProcessCPUTime()
    ->UseRealTime();

int main(int argc, char** argv) {
   ::benchmark::Initialize(&argc, argv);
   ::benchmark::RunSpecifiedBenchmarks();
}
