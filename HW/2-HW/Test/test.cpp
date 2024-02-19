#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../SRC/HashMap.hpp"
#include "../SRC/Linear.hpp"
#include "../SRC/Tree.hpp"
#include "string"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>


using std::cout;
using std::endl;


// Testing the HashMap class



// Testing creating the test object


TEST_CASE("Testing the HashMap class: Ints") {
    // HashMap
    HashMap<int> map({1,2,3,4,5,6,7,8,9,10}, 10);

    SECTION("Testing hashkey"){
        // hashKey
        REQUIRE(map.hashKey(1) == 1);
        REQUIRE(map.hashKey(2) == 2);
    }
    SECTION("Testing insertElement"){
        // insertElement
        // integer insertion
        map.insertElement(11);
        REQUIRE(map.hashKey(11) == 1);
    }
    SECTION("Testing search"){
        // search
        // integer search
        REQUIRE(map.search(1) == true);
        REQUIRE(map.search(10) == true);
        REQUIRE(map.search(22) == false);
    }
    SECTION("Testing deleteElement"){
        // deleteElement
        // integer deletion
        map.deleteElement(1);
        REQUIRE(map.search(1) == false);
    }
}

TEST_CASE("Testing the HashMap class: Strings") {
  // HashMap
  HashMap<std::string> map({"one","two","three","four","five","six","seven","eight","nine","ten"}, 10);

  SECTION("Testing hashkey"){
    // hashKey
    //testing if the hashkey is the same for the same string
    // the hashkey is not predictable so we can only test if it is consistent
      auto oneHash = map.hashKey("one");
      REQUIRE(map.hashKey("one") == oneHash);
      auto twoHash = map.hashKey("two");
      REQUIRE(map.hashKey("two") == twoHash);
  }
  SECTION("Testing insertElement"){
      // insertElement
      // string insertion
      map.insertElement("eleven");
      auto elevenHash = map.hashKey("eleven");
      REQUIRE(map.hashKey("eleven") == elevenHash);
  }
    SECTION("Testing search"){
        // search
        // string search
        REQUIRE(map.search("one") == true);
        REQUIRE(map.search("ten") == true);
        REQUIRE(map.search("twentytwo") == false);
    }
    SECTION("Testing deleteElement"){
        // deleteElement
        // string deletion
        map.deleteElement("one");
        REQUIRE(map.search("one") == false);
    }
}


// Testing the Linear class
TEST_CASE("Testing the Linear class: Ints") {
    // Linear
    Linear<int> l;

    l.insertElement(1);//Got an error here, the sections blocked others from seeing the insertion so i moved it out, chatGPT helped debug
    l.insertElement(2);
    l.insertElement(3);
    l.insertElement(4);
    l.insertElement(5);

    SECTION("Testing insertElement"){
        // check elements
        REQUIRE(l.getElementAtIndex(0) == 1);
        REQUIRE(l.getElementAtIndex(1) == 2);
        REQUIRE(l.getElementAtIndex(2) == 3);
        REQUIRE(l.getElementAtIndex(3) == 4);
        REQUIRE(l.getElementAtIndex(4) == 5);
    }
    SECTION("Testing search"){
        // search
        REQUIRE(l.search(1) == true);
        REQUIRE(l.search(5) == true);
        REQUIRE(l.search(22) == false);
    }
    SECTION("Testing deleteElement"){
        // deleteElement
        l.deleteElement(1);
        REQUIRE(l.search(1) == false);
    }
}

TEST_CASE("Testing the Linear class: Strings") {
    // Linear
    Linear<std::string> l;

    l.insertElement("one");
    l.insertElement("two");
    l.insertElement("three");
    l.insertElement("four");
    l.insertElement("five");

    SECTION("Testing insertElement"){
        // check elements
        REQUIRE(l.getElementAtIndex(0) == "one");
        REQUIRE(l.getElementAtIndex(1) == "two");
        REQUIRE(l.getElementAtIndex(2) == "three");
        REQUIRE(l.getElementAtIndex(3) == "four");
        REQUIRE(l.getElementAtIndex(4) == "five");
    }
    SECTION("Testing search"){
        // search
        REQUIRE(l.search("one") == true);
        REQUIRE(l.search("five") == true);
        REQUIRE(l.search("twentytwo") == false);
    }
    SECTION("Testing deleteElement"){
        // deleteElement
        l.deleteElement("one");
        REQUIRE(l.search("one") == false);
    }
}

// Testing the Tree class
TEST_CASE("Testing the Tree class: Ints") {
    // Tree
    Tree<int> t(5);
    t.insertElement(t.getRoot(), 3);
    t.insertElement(t.getRoot(), 7);
    t.insertElement(t.getRoot(), 2);
    t.insertElement(t.getRoot(), 4);
    t.insertElement(t.getRoot(), 6);
    t.insertElement(t.getRoot(), 8);

    SECTION("Testing insertElement"){
        // check elements
        REQUIRE(t.search(t.getRoot(), 3) == true);
        REQUIRE(t.search(t.getRoot(), 7) == true);
        REQUIRE(t.search(t.getRoot(), 2) == true);
        REQUIRE(t.search(t.getRoot(), 4) == true);
        REQUIRE(t.search(t.getRoot(), 6) == true);
        REQUIRE(t.search(t.getRoot(), 8) == true);
    }
    SECTION("Testing search"){
        // search
        REQUIRE(t.search(t.getRoot(), 3) == true);
        REQUIRE(t.search(t.getRoot(), 7) == true);
        REQUIRE(t.search(t.getRoot(), 22) == false);
    }
    SECTION("Testing deleteElement"){
        // deleteElement
        t.deleteElement(t.getRoot(), 3);
        REQUIRE(t.search(t.getRoot(), 3) == false);
    }
}