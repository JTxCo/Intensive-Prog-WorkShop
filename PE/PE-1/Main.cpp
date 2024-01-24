#include <iostream>
#include <vector>
#include "Point.h"
using std::cout;
using std::vector;

int main(){
    //using the default 0s
    Point<float> point2d(2);
    Point<float> point3d(3);
    Point<float> point4d(4);
    

    //using given numbers
    vector<float> coordinates2d = {1,2};
    vector<float> coordinates3d = {1,2,3};
    vector<float> coordinates4d = {1,2,3,4};

    Point<float> point2d_given(coordinates2d);
    Point<float> point3d_given(coordinates3d);
    Point<float> point4d_given(coordinates4d);

    //adding all of the points to a vector so it is easier to iterate through
    vector<Point<float>> points = {point2d, point3d, point4d, point2d_given, point3d_given, point4d_given};

    //calculating the distance between the points

    //distance betwenen 2d points
    //points are at
    cout << "Point 1 is at " << point2d.getCoordinate(0) << ", " << point2d.getCoordinate(1) << endl;
    cout << "Point 2 is at " << point2d_given.getCoordinate(0) << ", " << point2d_given.getCoordinate(1) << endl;
    cout << "Distance between point 1 and point 2 is " << point2d.Distance_between_point(point2d_given) << endl;
    //distance between 3d points
    cout << "Point 3 is at " << point3d.getCoordinate(0) << ", " << point3d.getCoordinate(1) << ", " << point3d.getCoordinate(2) << endl;
    cout << "Point 4 is at " << point3d_given.getCoordinate(0) << ", " << point3d_given.getCoordinate(1) << ", " << point3d_given.getCoordinate(2) << endl;
    cout << "Distance between point 3 and point 4 is " << point3d.Distance_between_point(point3d_given) << endl;
    //distance between 4d points
    cout << "Point 5 is at " << point4d.getCoordinate(0) << ", " << point4d.getCoordinate(1) << ", " << point4d.getCoordinate(2) << ", " << point4d.getCoordinate(3) << endl;
    cout << "Point 6 is at " << point4d_given.getCoordinate(0) << ", " << point4d_given.getCoordinate(1) << ", " << point4d_given.getCoordinate(2) << ", " << point4d_given.getCoordinate(3) << endl;
    cout << "Distance between point 5 and point 6 is " << point4d.Distance_between_point(point4d_given) << endl;

  
    //translating a postive distnace
    //translating 2d points
    cout << "Point 1 is at " << point2d.getCoordinate(0) << ", " << point2d.getCoordinate(1) << endl;
    cout<< "point is translated by 2"<<endl;
    point2d.translate(2);
    cout << "Point 1 is now at " << point2d.getCoordinate(0) << ", " << point2d.getCoordinate(1) << endl;
    //distance between 2d points updated
    cout<< "Distance between point 1 and point 2 is now " << point2d.Distance_between_point(point2d_given) << endl;


    //translating a negative distance on the 2d point
    cout<< "point is translated by -2"<<endl;
    point2d.translate(-2);
    cout << "Point 1 is now at " << point2d.getCoordinate(0) << ", " << point2d.getCoordinate(1) << endl;
    //distance between 2d points updated
    cout<< "Distance between point 1 and point 2 is now " << point2d.Distance_between_point(point2d_given) << endl;

    return 0;
}



