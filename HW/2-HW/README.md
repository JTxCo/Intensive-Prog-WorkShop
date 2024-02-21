## Benchmarks

This project's performance tests are implemented using the [Google Benchmark](https://github.com/google/benchmark) library.



The results of the benchmark are included here for reference:
    They will change depending on the machine and the compiler used.
    Each time the benchmark is run, the results will be different.



    Run on (16 X 2400 MHz CPU s)
    CPU Caches:
    L1 Data 32 KiB
    L1 Instruction 32 KiB
    L2 Unified 256 KiB (x8)
    L3 Unified 16384 KiB
    Load Average: 1.96, 3.23, 4.24
    -----------------------------------------------------------------------
    Benchmark                             Time             CPU   Iterations
    -----------------------------------------------------------------------
    Bench_HashmapInsert_Integers   15842694 ns     15842000 ns           42
    Bench_HashmapInsert_Strings    14462167 ns     14455306 ns           49
    Bench_HashmapInsert_Decimals   17022243 ns     17015158 ns           38
    Bench_HashmapSearch_Integers        225 ns          225 ns      3167063
    Bench_HashmapSearch_Decimals        245 ns          245 ns      2909429
    Bench_HashmapSearch_Strings         697 ns          696 ns      1018004
    Bench_LinearInsert_Integers     1668868 ns      1668841 ns          409
    Bench_LinearInsert_Decimals     1807161 ns      1806710 ns          386
    Bench_LinearInsert_Strings      2510787 ns      2510777 ns          269
    Bench_LinearSearch_Integers      322189 ns       322084 ns         2082
    Bench_LinearSearch_Decimals      379597 ns       377979 ns         1808
    Bench_LinearSearch_Strings      1238571 ns      1236197 ns          559
    Bench_TreeInsert_Integers       9717732 ns      9687292 ns           72
    Bench_TreeInsert_Decimals       9970909 ns      9951424 ns           66
    Bench_TreeInsert_Strings       53360777 ns     53235818 ns           11
    Bench_TreeSearch_Integers           437 ns          436 ns      1678967
    Bench_TreeSearch_Decimals           419 ns          418 ns      1610580
    Bench_TreeSearch_Strings           7742 ns         7718 ns        94994