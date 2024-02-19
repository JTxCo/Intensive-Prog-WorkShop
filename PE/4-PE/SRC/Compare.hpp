#include "vector"
#include <iostream>

/*
instructions for Compare.hpp


Create a class named Compare. This should be a templated class. Given that it is a templated class, you will need to implement your header and implementation in the same file.

Fields:

1. The Compare class should have a private field storing a generic std::vector<T>

Methods:

1. std::vector<T> getLessThan(T val); //returns all matches that are less than val
2. std::vector<T> getGreaterThan(T val); //returns all matches that are greater than val
3. int matches(T val); //if there are exact matches of values in the vectors, then it returns the number of matches
Remember to include necessary constructors in your class.
*/
struct myType{
    int x;
    int y;
    
    myType(){
        x = 0;
        y = 0;
    }

    // Define how "less than" should be evaluated for myType
    bool operator<(const myType & rhs) const {
        // example: compare based on the sum of x and y
        return x + y < rhs.x + rhs.y;
    }

    // Define how "greater than" should be evaluated for myType
    bool operator>(const myType & rhs) const {
        // example: compare based on the sum of x and y
        return x + y > rhs.x + rhs.y;
    }

    // Define how "equality" should be evaluated for myType
    bool operator==(const myType & rhs) const {
        // example: consider them equal if both x and y match
        return x == rhs.x && y == rhs.y;
    }
};



template <typename T> class Compare {
    private:
        std::vector<T> vec;
    public:
        Compare(std::vector<T> v) {
            vec = v;
        }
        std::vector<T> getLessThan(T val) {
            std::vector<T> lessThan;
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i] < val) {
                    lessThan.push_back(vec[i]);
                }
            }
            return lessThan;
        }
        std::vector<T> getGreaterThan(T val) {
            std::vector<T> greaterThan;
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i] > val) {
                    greaterThan.push_back(vec[i]);
                }
            }
            return greaterThan;
        }
        int matches(T val) {
            int count = 0;
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i] == val) {
                    count++;
                }
            }
            return count;
        }
};

