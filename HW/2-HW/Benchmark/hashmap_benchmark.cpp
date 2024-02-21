#include <benchmark/benchmark.h>
#include "../SRC/HashMap.hpp"
#include "string"
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <random>
#include <filesystem>

#include "common.h"



/*
    This file contains implementation for building a hashmap and performance benchmarking for operations

    The first section is benchmarking the insertion of elements into the hashmap. The data is read from the input files

*/





void bench_hashmapInsert(benchmark::State& state, const std::string& filepath, DataType type) {
    if (!DoesFileExist(filepath)) {
        std::cout << "File does not exist at path: " << filepath << '\n';
        return;
    }
    switch(type){
        case(DataType::INTEGER): {
            auto data = readIntegers(filepath); 
            for(auto _ : state) {
                HashMap<int> map(data, data.size());
            }
            break;
        }
        case(DataType::STRING): {
            auto data = readStrings(filepath);
            for(auto _ : state) {
                HashMap<std::string> map(data, data.size());
            }
            break;
        }
        case(DataType::DECIMAL): {
            auto data = readDecimals(filepath);
            for(auto _ : state) {
                HashMap<double> map(data, data.size());
            }
            break;
        }
        default:
            break; //hopefully does not get called but if it does it is here
    }
}


void Bench_HashmapInsert_Integers(benchmark::State& state) {
    bench_hashmapInsert(state, INTEGERS_CSV, DataType::INTEGER);
}

void Bench_HashmapInsert_Strings(benchmark::State& state) {
    bench_hashmapInsert(state, STRINGS_CSV, DataType::STRING);
}

void Bench_HashmapInsert_Decimals(benchmark::State& state) {
    bench_hashmapInsert(state, DECIMALS_CSV, DataType::DECIMAL);
}

BENCHMARK(Bench_HashmapInsert_Integers);
BENCHMARK(Bench_HashmapInsert_Strings);
BENCHMARK(Bench_HashmapInsert_Decimals);

// Next section is benchmarking the search operation in the hashmap


template <typename T>
void bench_hashmapSearch(benchmark::State& state, HashMap<T>& map, std::vector<T>& data) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, data.size() - 1);
    for(auto _ : state) {
        // serach for first element in the data
        benchmark::DoNotOptimize(map.search(data.front()));
        // search for last element in the data
        benchmark::DoNotOptimize(map.search(data.back()));
        // search for random elements in the data
        benchmark::DoNotOptimize(map.search(data[dis(gen)]));
    }
}




void bench_hashmapSearch(benchmark::State& state, const std::string& filepath, DataType type) {
    if (!DoesFileExist(filepath)) {
        std::cout << "File does not exist at path: " << filepath << '\n';
        return;
    }
    switch(type){
        case(DataType::INTEGER): {
            auto data = readIntegers(filepath);
            HashMap<int> map(data, data.size());
            bench_hashmapSearch(state, map, data);
            break;
        }
        case(DataType::STRING): {
            auto data = readStrings(filepath);
            HashMap<std::string> map(data, data.size());
            bench_hashmapSearch(state, map, data);
            break;
        }
        case(DataType::DECIMAL): {
            auto data = readDecimals(filepath);
            HashMap<double> map(data, data.size());
            bench_hashmapSearch(state, map, data);
            break;
        }
        default:
            break; //hopefully does not get called but if it does it is here
    }
}


void Bench_HashmapSearch_Integers(benchmark::State& state) {
    bench_hashmapSearch(state, INTEGERS_CSV, DataType::INTEGER);
}

void Bench_HashmapSearch_Decimals(benchmark::State& state) {
    bench_hashmapSearch(state, DECIMALS_CSV, DataType::DECIMAL);
}

void Bench_HashmapSearch_Strings(benchmark::State& state) {
    bench_hashmapSearch(state, STRINGS_CSV, DataType::STRING);
}
BENCHMARK(Bench_HashmapSearch_Integers);
BENCHMARK(Bench_HashmapSearch_Decimals);
BENCHMARK(Bench_HashmapSearch_Strings);

