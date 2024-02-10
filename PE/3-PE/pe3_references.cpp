#include <iostream>
using std::cout;
using std::endl;
#include "pe3_references.h"
// Name:
//

// Write any functions you need here!


void modify(int *ptr){
    *ptr = *ptr + 1;
}
void modify2(int &ref){
    ref = ref + 1;
}
void modify3(const int &ref, int *ptr){
    (*ptr)++;
}

// MyClass implementation

MyClass::MyClass(int x){
    this->x = x;
}
int MyClass::get_x() {
    return this->x;
}
bool MyClass::operator==(const MyClass &other){
    return this->x == other.x;
}
MyClass MyClass::operator+(const MyClass &other){
    return MyClass(this->x + other.x);
}


