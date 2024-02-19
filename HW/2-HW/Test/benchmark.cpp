#include <benchmark/benchmark.h>
#include "../SRC/HashMap.hpp"
#include "../SRC/Linear.hpp"
#include "../SRC/Tree.hpp"
#include "string"
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <random>


static const int ROOT_VALUE = 5;
static const string INTEGERS_CSV = "../CSv_Data/integers.csv";
static void Bench_TreeInsert(benchmark::State& state) {
    for(auto _ : state) {
        Tree<int> tree(ROOT_VALUE);
        for(int i = 0; i < state.range(0); ++i)
            tree.insertElement(i);
    }
}
BENCHMARK(Bench_TreeInsert)->Range(8, 8<<10);

static void Bench_TreeSearch_First(benchmark::State& state) {
    Tree<int> tree(ROOT_VALUE);
    for(int i = 0; i < state.range(0); ++i)
        tree.insertElement(i);

    for(auto _ : state)
        benchmark::DoNotOptimize(tree.search(ROOT_VALUE));
}
BENCHMARK(Bench_TreeSearch_First)->Range(8, 8<<10);

static void Bench_TreeSearch_Last(benchmark::State& state) {
    Tree<int> tree(ROOT_VALUE);
    for(int i = 0; i < state.range(0); ++i)
        tree.insertElement(i);

    for(auto _ : state)
        benchmark::DoNotOptimize(tree.search(state.range(0) - 1));
}
BENCHMARK(Bench_TreeSearch_Last)->Range(8, 8<<10);

static void Bench_TreeSearch_Random(benchmark::State& state) {
    Tree<int> tree(ROOT_VALUE);
    for(int i = 0; i < state.range(0); ++i)
        tree.insertElement(i);

    std::random_device rd;  
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> distr(0, state.range(0) - 1);

    for(auto _ : state)
        benchmark::DoNotOptimize(tree.search(distr(gen)));
}
BENCHMARK(Bench_TreeSearch_Random)->Range(8, 8<<10);

BENCHMARK_MAIN();
