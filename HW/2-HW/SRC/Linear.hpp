/*
Instructions for Linear.hpp:
Linear - using vectors
Below are the interfaces for the classes you will implement. You may include additional functions as needed.  Note: it is your job to determine which parameters and methods should be const!
(this was a table copied in)
Function Signatures	Description
Linear()	Default constructor

void insertElement(T val)	Insert element at the last position in the vector. You should insert the elements in the order it is provided. You should not be sorting it at insertion.
T getElementAtIndex(int index)	
Return element at specified index
bool search(T val)	Returns if the element is found in the vector
void deleteElement (T val)	Delete the element from the vector
std::ostream& operator<<(std::ostream& os, const Linear<U> &l);	overload the << operator for Linear<T>. This should print out the contents of the vector in Linear in the format: {T, T, T, T}



*/
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;


template <typename T>
class Linear {
    private:
        vector<T> vec;
    public:
        // constructor
        Linear() = default;
        // destructor
        ~Linear() = default;
        // insertElement
        void insertElement(T val) {
            vec.push_back(val);
        }
        // getElementAtIndex
        T getElementAtIndex(int index) {
            return vec[index];
        }
        // search
        bool search(T val) {
            for (auto element : vec) {
                if (element == val) {

                    return true;
                }
            }
            return false;
        }
        // deleteElement
        void deleteElement(T val) {
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i] == val) {
                    vec.erase(vec.begin() + i);
                    return;
                }
            }
        }
        // operator<<
        friend std::ostream& operator<<(std::ostream& os, const Linear<T> &l) {
            os << "{";
            for (int i = 0; i < l.vec.size(); i++) {
                os << l.vec[i];
                if (i != l.vec.size() - 1) {
                    os << ", ";
                }
            }
            os << "}";
            return os;
        }
};

