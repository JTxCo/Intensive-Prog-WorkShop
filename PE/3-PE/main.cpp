#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;

#include "pe3_references.h"




int main() {
    // Add as many prints to cout as you need to answer the questions.
    // Leave them in your code when you turn it in.
    // If you have lines of code that cause errors that test the questions,
    // leave this code in your file but comment it out.
    
    // 1) Declare an int
    int x = 5;

    // 2) Declare a pointer to that int
    int *ptr = &x;

    // 3) Increment the int via the pointer
    *ptr = *ptr + 1; 
    // 4) Declare a reference to your int
    int &ref = x;
    // 5) Increment the int via the reference
    ref = ref + 1;
    // 6) When you increment the int via the variable declared in #1, which
    // variables will be modified to see the changes? (the pointer , reference or both?)
    // Answer: 
    cout<<"Incrementing x:"<<endl;
    x++;
    cout<<"pointer: "<<*ptr<<endl;
    cout<<"reference: "<<ref<<endl;
    // this shows it will output the same value for both the pointer and the reference


    // 7) When you increment the int via the pointer declared in #2, which
    // variables will be modified to see the changes?
    // Answer: 
    cout<<"Pointer increment:"<<endl;
    *ptr = *ptr + 1;
    cout<<"pointer: "<<*ptr<<endl;
    cout<<"reference: "<<ref<<endl;
    cout<<"x: "<<x<<endl;
    // 8) When you increment the int via the reference declared in #4, which
    // variables will be modified to see the changes?
    // Answer: 
    cout<<"Reference increment:"<<endl;
    ref = ref + 1;
    cout<<"pointer: "<<*ptr<<endl;
    cout<<"reference: "<<ref<<endl;
    cout<<"x: "<<x<<endl;
    // 9) Write a function that takes an int * parameter. How would you pass the 
    // variable from #1 into this function? 
    // Modify the parameter within the function using any operation of your choice.(write the function definition and call below)
    // Does it update the value you originally passed to the function?
    cout<<"Before modify: "<<x<<endl;
    modify(&x);
    cout<<"After modify: "<<x<<endl;

    // 10) Can you pass your reference from #4 to the function from #9 without accessing its address?
    // Answer:
    cout<<"Before modify: "<<ref<<endl;
    modify(&ref);
    cout<<"After modify: "<<ref<<endl;
    // 11) Write a function that takes an int & parameter. How would you pass the 
    // variable from #1 into this function? 
    // Modify the parameter using any operation of your choice.(write the function definition and call below)
    // Does it update the value you originally passed to the function?
    cout<<"new function by &ref"<<endl;
    cout<<"Before modify: "<<x<<endl;
    modify2(x);
    cout<<"After modify: "<<x<<endl;
    // 12) Can you pass your pointer from #2 to the function from #11 without dereferencing it?
    // Answer:
    cout<<"Passing pointer to modify2"<<endl;
    cout<<"Before modify: "<<*ptr<<endl;
    modify2(*ptr);
    cout<<"After modify: "<<*ptr<<endl;
    // 13) Can you pass your reference from #4 to the function from #11?
    // Answer:
    cout<<"Passing reference to modify2"<<endl;
    cout<<"Before modify: "<<ref<<endl;
    modify2(ref);
    cout<<"After modify: "<<ref<<endl;

    // 14) Write a function that takes one const reference input parameter and one pointer
    // output parameter. The function should fill in the value of the output parameter based
    // on the value of the input parameter. (what it does exactly is up to you).
    // Call your function 3 times below. Be sure to include output as necessary to be sure
    // your function works as described.
    cout<<"modify 3"<<endl;
    int y = 5;
    int z;
    modify3(y, &z);
    cout<<"z: "<<z<<endl;
    modify3(x, &z);
    cout<<"z: "<<z<<endl;
    modify3(ref, &z);
    cout<<"z: "<<z<<endl;


    // 15) What is/are the difference(s) between output parameters and return values?
    // Answer:
    // output parameters are passed by reference and are modified within the function
    // return values are passed by value and are returned from the function


    // 16) Create a custom class with at least one private field/class attribute. Overload the == and + operator for this class
    // such that == can be used to compare the objects of the class and + can be used to add
    // 2 objects of the class together. Implement an appropriate constructor for your class.
    // When you overload these operators, the resulting return value should make sense.
    // Instantiate at least 2 objects of this class and perform the == and + operations on them.
    // hint: for operator+, the function signature when implemented as a member function of the Object class is:
    // Object operator+(const Object &other)
    // Answer:

    MyClass a(5);
    MyClass b(21);
    MyClass c(5);

    cout<<"a==b: "<<(a==b)<<endl;
    cout<<"a==c: "<<(a==c)<<endl;
    cout<<"a+b: "<<(a+b==MyClass(26))<<endl;
    cout<<"b+c: "<<(b+c==MyClass(26))<<endl;
    cout<<"a+b+c: "<<(a+b+c==MyClass(31))<<endl;
    cout<<"a+c:"<< (a+c==MyClass(10))<<endl;

}
