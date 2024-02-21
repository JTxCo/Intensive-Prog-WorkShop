#include <benchmark/benchmark.h>
#include "../SRC/Linear.hpp"
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
    This file contains implementation for building a linear list and performance benchmarking for operations

    The first section is benchmarking the insertion of elements into the list. The data is read from the input files

*/


void bench_linearInsert(benchmark::State& state, const std::string& filepath, DataType type) {
    if (!DoesFileExist(filepath)) {
        std::cout << "File does not exist at path: " << filepath << '\n';
        return;
    }
    switch(type){
        case(DataType::INTEGER): {
            auto data = readIntegers(filepath); 
            for(auto _ : state) {
                Linear<int> list;
                for(const int &value : data) {
                    list.insertElement(value);
                }
            }
            break;
        }
        case(DataType::STRING): {
            auto data = readStrings(filepath);
            for(auto _ : state) {
                Linear<std::string> list;
                for(const std::string &value : data) {
                    list.insertElement(value);
                }
            }
            break;
        }
        case(DataType::DECIMAL): {
            auto data = readDecimals(filepath);
            for(auto _ : state) {
                Linear<double> list;
                for(const double &value : data) {
                    list.insertElement(value);
                }
            }
            break;
        }
        default:
            break; //hopefully does not get called but if it does it is here

    }
}


void Bench_LinearInsert_Integers(benchmark::State& state) {
    bench_linearInsert(state, INTEGERS_CSV, DataType::INTEGER);
}

void Bench_LinearInsert_Strings(benchmark::State& state) {
    bench_linearInsert(state, STRINGS_CSV, DataType::STRING);
}

void Bench_LinearInsert_Decimals(benchmark::State& state) {
    bench_linearInsert(state, DECIMALS_CSV, DataType::DECIMAL);
}

BENCHMARK(Bench_LinearInsert_Integers);
BENCHMARK(Bench_LinearInsert_Decimals);
BENCHMARK(Bench_LinearInsert_Strings);



// Next section is benchmarking the search operation in the list

template <typename T>
void bench_linearSearch(benchmark::State& state, Linear<T>& list, const std::vector<T>& data) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, data.size() - 1);
    for(auto _ : state) {
        // searh for first element in the list
        benchmark::DoNotOptimize(list.search(data.front()));
        // search for last element in the list
        benchmark::DoNotOptimize(list.search(data.back()));
        // search for random element in the list
        benchmark::DoNotOptimize(list.search(data[dis(gen)]));

    }
}



void Bench_LinearSearch(benchmark::State& state, const std::string& filepath, DataType type) {
    if (!DoesFileExist(filepath)) {
        std::cout << "File does not exist at path: " << filepath << '\n';
        return;
    }
    switch(type){
        case(DataType::INTEGER): {
            auto data = readIntegers(filepath);
            Linear<int> list;
            for(const int &value : data) {
                list.insertElement(value);
            }
            bench_linearSearch(state, list, data);
            break;
        }
        case(DataType::STRING): {
            auto data = readStrings(filepath);
            Linear<std::string> list;
            for(const std::string &value : data) {
                list.insertElement(value);
            }
            bench_linearSearch(state, list, data);
            break;
        }
        case(DataType::DECIMAL): {
            auto data = readDecimals(filepath);
            Linear<double> list;
            for(const double &value : data) {
                list.insertElement(value);
            }
            bench_linearSearch(state, list, data);
            break;
        }
        default:
            break; //hopefully does not get called but if it does it is here
    }
}


void Bench_LinearSearch_Integers(benchmark::State& state) {
    Bench_LinearSearch(state, INTEGERS_CSV, DataType::INTEGER);
}
void Bench_LinearSearch_Strings(benchmark::State& state) {
    Bench_LinearSearch(state, STRINGS_CSV, DataType::STRING);
}
void Bench_LinearSearch_Decimals(benchmark::State& state) {
    Bench_LinearSearch(state, DECIMALS_CSV, DataType::DECIMAL);
}

BENCHMARK(Bench_LinearSearch_Integers);
BENCHMARK(Bench_LinearSearch_Decimals);
BENCHMARK(Bench_LinearSearch_Strings);