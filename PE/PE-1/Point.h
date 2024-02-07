#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;


template <typename T>
class Point{
private:
    vector<T> coordinates;

public: 
    // Default constructor for n-dimensional point
    Point(size_t n);

    // Constructor for multiple coordinates, but given numbers
    Point(const vector<T>& coordinates);

    // Get the coordinate at index i, this is using 0 based indexing
    T getCoordinate(int i) const;

    // Get the dimensions of the point
    size_t getDimensions() const;
    
    //get the distance between the point and another point
    float Distance_between_point(const Point<T>& p1) const;

    //translate the point by a number n
    void translate(T n);
    
};


#endif // POINT_H