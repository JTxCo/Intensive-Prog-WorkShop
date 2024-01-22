#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include "functions_to_implement.h"
TEST_CASE("Split returns a vector of strings", "[split]"){
    REQUIRE(Split("hello world", " ") == std::vector<std::string>({"hello", "world"}));
    REQUIRE(Split("hello world", "o") == std::vector<std::string>({"hell", " w", "rld"}));
}


TEST_CASE("VECTOR MATCHING", "[match]"){
    vector<int> a = {1,2,3,4,5,6,7,8,9};
    const vector<int> b = {1,3,5,7,9};
    vector<int> c = MatchVectors(a,b);
    REQUIRE(c == std::vector<int>({2,4,6,8}));
}

TEST_CASE("MULTIPLES FILTER", "[filter]"){
    vector <int> d = {1,2,3,4,5,6,7,8,9};
    d = MultiplesFilter(d, 3);
    REQUIRE(d == std::vector<int>({1,2,4,5,7,8}));
}
TEST_CASE("Dividing by too large num", "[filter]"){
    vector <int> d = {1,2,3,4,5,6,7,8,9};
    d = MultiplesFilter(d, 10);
    REQUIRE(d == std::vector<int>({1,2,3,4,5,6,7,8,9}));
}