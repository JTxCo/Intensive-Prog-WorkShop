#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Point.h"

using std::cout;
using std::vector;
using std::endl;

// Default constructor for n-dimensional point
template <typename T>
Point<T>::Point(size_t n) {
    coordinates.resize(n, 0);
}

// Constructor for multiple coordinates, but given numbers
template <typename T>
Point<T>::Point(const vector<T>& coordinates) : coordinates(coordinates) {}

// Get the coordinate at index i, this is using 0 based indexing
template <typename T>
T Point<T>::getCoordinate(int i) const {
    return coordinates[i];
}

// Get the dimensions of the point
template <typename T>
size_t Point<T>::getDimensions() const {
    return coordinates.size();
}

// Returns the distance between the point and another point
template <typename T>
float Point<T>::Distance_between_point(const Point<T>& p1) const {
    if (p1.getDimensions() != this->getDimensions()) {
        throw std::invalid_argument("Points are not in the same dimension\n point dimensions: " + std::to_string(this->getDimensions()) + "\n p1 dimensions: " + std::to_string(p1.getDimensions()) + "\n");

    }

    float sum = 0;
    for (size_t i = 0; i < p1.getDimensions(); i++) {
        sum += std::pow((p1.getCoordinate(i) - this->getCoordinate(i)), 2);
    }

    return std::sqrt(sum);
}

// Translate the point by a number n
template <typename T>
void Point<T>::translate(T n){
    for (size_t i = 0; i < this->getDimensions(); i++)
    {
        this->coordinates[i]+=n;
    }
}


template class Point<int>;
template class Point<float>;
template class Point<double>;
template class Point<long>;
