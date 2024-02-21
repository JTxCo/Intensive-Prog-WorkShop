#include <iostream>
#include <vector> 
using namespace std;

// scope: "what can we see right here"
// - what variables/functions/other can we access from inside x, where x is a function, method, etc.

// 1) what happens in c++ if you try to acces a variable out of scope?

// 2) what happens if we make everything global?


// Summary:
// pass-by-value vs. pass-by-reference
// pass-by-value: give the function a copy of the value
// pass-by-reference: give the address of the location of the value


// *************************************************


// When you are done: turn in your file on canvas

// Names (be sure to include the initial of your last name(s)!):
//

// 1) Write a function that demonstrates whether ints are pass-by-value or pass-by-reference
// (do not use pointers or c++ references in this function)
// Answer:
int int_func(int x) {
    x += 5;
    return x;
}


// 2) Write a function that tests demonstrates whether strings (std::string) are pass-by-value or pass-by-reference
// (do not use pointers or c++ references in this function)
// Answer:

string string_func(string s) {
    s += " General Kenobi";
    return s;
}



// 3) Write a function that demonstrates whether arrays are pass-by-value or pass-by-reference
// recall: to initialize an array-- type name[] = {comma separated elements};
// (do not use pointers or c++ references in this function)
// Answer:

int array_func(int arr[]) {
    arr[0] = 5;
    return arr[0];
}



// 4) Write a function that demonstrates whether vectors are pass-by-value or pass-by-reference
// Answer:

vector<int> vector_func(vector<int> v) {
    v.push_back(5);
    return v;
}

int main() {
    // code to call your functions goes here.
    // you may find it useful to print out values in main as well as inside your functions
    // to appropriately demonstrate whether the given type is pass-by-value or 
    // pass-by-reference
    int x = 3;
    printf("int_func: %d\n", int_func(x));
    if(x == 3) {
        printf("pass-by-value\n");
    } else {
        printf("pass-by-reference\n");
    }

    string s = "hello there";
    printf("string_func: %s\n", string_func(s).c_str());
    if(s == "hello there") {
        printf("pass-by-value\n");
    } else {
        printf("pass-by-reference\n");
    }

    int arr[] = {1, 2, 3};
    printf("array_func: %d\n", array_func(arr));
    if(arr[0] == 1) {
        printf("pass-by-value\n");
    } else {
        printf("pass-by-reference\n");
    }

    vector<int> v = {1, 2, 3};
    printf("vector_func: %d\n", vector_func(v)[3]);
    if(v[3] == 5) {
        printf("pass-by-reference\n");
    } else {
        printf("pass-by-value\n");
    }
}
