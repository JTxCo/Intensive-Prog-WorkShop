#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "pe3_references.h"

// instructions
// You will write test cases for the functions/methods you implement in #9, #11, #14 and #16 in test.cpp. Once you have written your test file, make sure that you can generate your test executable using the Makefile. 


TEST_CASE("modify with negative numbers"){
    int x = -5;
    modify(&x);
    REQUIRE(x == -4);
}

TEST_CASE("modify2 with zero"){
    int y = 0;
    modify2(y); 
    REQUIRE(y == 1);  
}

TEST_CASE("modify3 with large numbers"){
    int z = 1000000;
    int a = 1500000;
    modify3(z, &a);  
    REQUIRE(a == 1500001);  
}

TEST_CASE("MyClass multiple addition"){
    MyClass obj1(5);
    MyClass obj2(7);
    MyClass obj3(10);
    MyClass sum = obj1 + obj2 + obj3;
    REQUIRE(sum.get_x() == 22);
}

