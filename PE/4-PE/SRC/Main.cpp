
/*
Test your Compare class with different types:
Instantiate your class with at least 2 different pre-defined datatypes (eg. int, double) and 1 user-defined (a class or struct of your choice) type. Make calls to each method with the different objects and print the results.
Note that the Gradescope autograder will verify using a vector of ints.
Note: For the user-defined types, you may have to implement some operator overloads for this class to function as expected.
*/
#include <iostream>
#include "Compare.hpp"
#include <vector>




int main(){
    // int define
    std::vector<int> intVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Compare<int> intCompare(intVec);
    std::cout << "Ints less than 5: ";
    std::vector<int> lessThanInts = intCompare.getLessThan(5);
    for (const auto& val : lessThanInts) {
        std::cout << val << " ";
    }
    std::cout << std::endl;  

    std::cout << "Ints greater than 5: ";
    std::vector<int> greaterThanInts = intCompare.getGreaterThan(5);
    for (const auto& val : greaterThanInts) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout<<"Ints equal to 5: "<<intCompare.matches(5)<<std::endl;


    // double define
    std::vector<double> doubleVec = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    Compare<double> doubleCompare(doubleVec);
    std::cout << "Doubles less than 5.5: ";
    std::vector<double> lessThanDoubles = doubleCompare.getLessThan(5.5);
    for (const auto& val : lessThanDoubles) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Doubles greater than 5.5: ";
    std::vector<double> greaterThanDoubles = doubleCompare.getGreaterThan(5.5);
    for (const auto& val : greaterThanDoubles) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout<<"Doubles equal to 5.5: "<<doubleCompare.matches(5.5)<<std::endl;

    // myType define
    std::vector<myType> myTypeVec = {myType(), myType(), myType(), myType(), myType(),
                                    myType(), myType(), myType(), myType(), myType()};
    Compare<myType> myTypeCompare(myTypeVec);

    std::vector<myType> lessThanResult = myTypeCompare.getLessThan(myType());
    std::vector<myType> greaterThanResult = myTypeCompare.getGreaterThan(myType());
    int matchesResult = myTypeCompare.matches(myType());

    std::cout << "myTypes less than myType: ";
    for (const auto& val : lessThanResult) {
        std::cout << "(" << val.x << "," << val.y << ") ";
    }
    std::cout << std::endl;

    std::cout << "myTypes greater than myType: ";
    for (const auto& val : greaterThanResult) {
        std::cout << "(" << val.x << "," << val.y << ") ";
    }
    std::cout << std::endl;

    std::cout << "myTypes equal to myType: " << matchesResult << std::endl;
    return 0;
}