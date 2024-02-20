#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Circle.h"


TEST_CASE ( "Factorials are computed", "[factorial]") {
  REQUIRE( Factorial(2) == 2 );
  REQUIRE( Factorial(3) == 6 );
  REQUIRE( Factorial(10) == 3628800 );
}


TEST_CASE("Circle constructor", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 5);
  REQUIRE(c.get_radius() == 5);
  REQUIRE(c.get_center().x == 0);
  REQUIRE(c.get_center().y == 0);
}


//this test fails with the given Circle.o

TEST_CASE("Circle Overalaps true", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 5);
  Circle c2(p, 5);
  REQUIRE(c.Overlaps(c2) == true);
}

//testing overap again
TEST_CASE("Circle overlaps", "[circle]") {
  Point p = {0, 0};
  Point p2 = {11, 11};
  Circle c(p, 5);
  Circle c2(p2, 5);
  REQUIRE(c.Overlaps(c2) == false);
}

TEST_CASE("Circle area", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 5);
  REQUIRE(c.CalculateArea() == 78);
}

TEST_CASE("Circle expand", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 5);
  c.Expand();
  REQUIRE(c.get_radius() == 6);
}

TEST_CASE("Circle shrink", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 5);
  c.Shrink();
  REQUIRE(c.get_radius() == 4);
}

TEST_CASE("Circle shrink to 0", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 0);
  c.Shrink();
  REQUIRE(c.get_radius() == 0);
}

TEST_CASE("Circle shrink negative", "[circle]") {
  Point p = {0, 0};
  Circle c(p, 0);
  c.Shrink();
  c.Shrink();
  REQUIRE(c.get_radius() == 0);
}