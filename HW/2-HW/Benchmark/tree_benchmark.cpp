#include <benchmark/benchmark.h>
#include "../SRC/HashMap.hpp"
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
#include <filesystem>

#include "common.h"


/*
    This file contains implementation for building a binary search tree (BST) and performance benchmarking for operations 
    on this tree. Following operations are performed and their brief descriptions are given:
    
    - Data Types: The file employs custom types to define the type of data being read from the input files.

    - Reading Data: The specified global variables hold paths to the input files. Functions designed to read these files 
      return the data in the form of vectors.

    - Insertion: These vectors serve as the data source for insertion into the Tree. The insert operation performance is 
      then benchmarked.

    - Searching: After all insertions, search operations are performed on the BST and their performances are benchmarked.

    Note: The insertions and searches are independent of each other. The performance of each operation is measured after 
    all insertions or searches have been completed.

    Benchmarking: Google benchmark library is used for the benchmarking the insertion and search operations. The timings 
    provided by these benchmarks give an estimation of relative operation speed under similar system load.
*/



template <typename T>
void benchInsert(std::vector<T> data, benchmark::State& state) {
    for(auto _ : state) {
        Tree<T> tree(data[0]);
        for(const T &value : data) {
            tree.insertElement(value);
        }
    }
}

void Bench_TreeInsert(benchmark::State& state, const std::string& filepath, DataType type) {
    if (!DoesFileExist(filepath)) {
        std::cout << "File does not exist at path: " << filepath << '\n';
        return;
    }
    switch(type){
        case(DataType::INTEGER): {
            auto data = readIntegers(filepath); 
            benchInsert(data, state);
            break;
        }
        
       case(DataType::DECIMAL): {
            auto data = readDecimals(filepath);
            benchInsert(data, state);
            break;
        }

        case(DataType::STRING): {
            auto data = readStrings(filepath);
            benchInsert(data, state);
            break;
        }
            
        default:
            break; // This should never happen, but just in case
    }
}   
void Bench_TreeInsert_Integers(benchmark::State& state) {
    Bench_TreeInsert(state, INTEGERS_CSV, DataType::INTEGER);
}
void Bench_TreeInsert_Decimals(benchmark::State& state) {
    Bench_TreeInsert(state,DECIMALS_CSV, DataType::DECIMAL);
}

void Bench_TreeInsert_Strings(benchmark::State& state) {
    Bench_TreeInsert(state, STRINGS_CSV, DataType::STRING);
}

BENCHMARK(Bench_TreeInsert_Integers);
BENCHMARK(Bench_TreeInsert_Decimals);
BENCHMARK(Bench_TreeInsert_Strings);


template <typename T>
void benchSearch(benchmark::State& state, Tree<T>& tree, std::vector<T> data) {
    const int dataSize = static_cast<int>(data.size());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, dataSize - 1);

    for(auto _ : state) {
        // Search first element
        benchmark::DoNotOptimize(tree.search(data.front()));
        // Search last element
        benchmark::DoNotOptimize(tree.search(data.back()));
        // Search random element
        benchmark::DoNotOptimize(tree.search(data[dis(gen)]));
    }
}

void Bench_TreeSearch(benchmark::State& state, const std::string& filepath, DataType type) {
    if (!DoesFileExist(filepath)) {
        std::cout << "File does not exist at path: " << filepath << '\n';
        return;
    }
    switch(type){
        case DataType::INTEGER: {
            auto data = readIntegers(filepath);
            Tree<int> tree(data[0]);
            for(const int &value : data) {
                tree.insertElement(value);
            }
            benchSearch(state, tree, data);
            break;
        }
        
        case DataType::DECIMAL: {
            auto data = readDecimals(filepath);
            Tree<double> tree(data[0]);
            for(const double &value : data) {
                tree.insertElement(value);
            }
            benchSearch(state, tree, data);
            break;
        }

        case DataType::STRING: {
            auto data = readStrings(filepath);
            Tree<std::string> tree(data[0]);
            for(const std::string &value : data) {
                tree.insertElement(value);
            }
            benchSearch(state, tree, data);
            break;
        }
            
        default:
            break;
    }
}

void Bench_TreeSearch_Integers(benchmark::State& state) {
    Bench_TreeSearch(state, INTEGERS_CSV, DataType::INTEGER);
}

void Bench_TreeSearch_Decimals(benchmark::State& state) {
    Bench_TreeSearch(state, DECIMALS_CSV, DataType::DECIMAL);
}

void Bench_TreeSearch_Strings(benchmark::State& state) {
    Bench_TreeSearch(state, STRINGS_CSV, DataType::STRING);
}

BENCHMARK(Bench_TreeSearch_Integers);
BENCHMARK(Bench_TreeSearch_Decimals);
BENCHMARK(Bench_TreeSearch_Strings);
