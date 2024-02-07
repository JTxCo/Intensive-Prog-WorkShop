#include "Circle.h"
#include <cmath>

unsigned int Factorial( unsigned int number ) {
  return number <= 1 ? number : Factorial(number-1)*number;
}



Circle::Circle(Point p, int rad) {
  center_ = p;
  radius_ = rad;
}


// I found that circle.o did not run correctly with the overalaps function so i rewrote it
// This was the only error i found
bool Circle::Overlaps(Circle& other) {
  int x1 = center_.x;
  int y1 = center_.y;
  int x2 = other.get_center().x;
  int y2 = other.get_center().y;
  int r1 = radius_;
  int r2 = other.get_radius();
  int distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  if (distance <= r1 + r2) {
    return true;
  }
  return false;
}

int Circle::CalculateArea() {
  return 3.14 * radius_ * radius_;
}

void Circle::Expand() {
  radius_++;
}

void Circle::Shrink() {
  if(radius_ > 0)
  radius_--;
}
