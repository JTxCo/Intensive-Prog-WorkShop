#include <iostream>
#include <string>
#include <vector>




// we'd like to write a function that is applicable to many types but
// we don't want to copy paste everything

// For example, here is a templated Add function
template <typename T>
T Add(T v1, T v2) {
    return v1 + v2;
}

// 6) implement a templated version of AddToValues, "AddToValues2".
template <typename T>
void AddToValues2(std::vector<T> &v1, T v2){
    v1.push_back(v2);
}


int main() {
    // 7) call AddToValues2, passing in an int vector and another int.
    std::vector<int> intVector;
    AddToValues2(intVector, 5);

    // 8) compile this file to object code
    // g++ -Wall -std=c++17 exercises2.cpp -c
    // then run: nm -C exercises2.o | grep "AddToValues2"
    // How many versions of the AddToValues2 function are in the
    // compiled object code? Copy + paste the relevant lines here:
    // 0000000000000080 T void AddToValues2<int>(std::__1::vector<int, std::__1::allocator<int>>&, int)

    // 9) call AddToValues2, passing in a vector of a non-int type and a value that you can add
    // successfully to the elements
    std::vector<std::string> stringVector;
    AddToValues2<std::string>(stringVector, "Hello");


    // 10) compile this file to object code
    // g++ -Wall -std=c++17 exercises2.cpp -c
    // then run: nm -C exercises2.o | grep "AddToValues2"
    // How many versions of the AddToValues2 function are in the
    // compiled object code? Copy + paste the relevant lines here:

// 0000000000000140 T void AddToValues2<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>(std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>>&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>)
// 00000000000000f0 T void AddToValues2<int>(std::__1::vector<int, std::__1::allocator<int>>&, int)    

    // 11) Experiment to find calls to this function that you would like to work but that do
    // not yet work. for each function call that doesn't work, comment about what type of 
    // error is produced.
    //  AddToValues2(stringVector, 5); // Error: no matching function for call to 'AddToValues2(std::vector<std::__cxx11::basic_string<char> >&, int)'
    //  AddToValues2(intVector, 5.0); // Error: no matching function for call to 'AddToValues2(std::vector<int>&, double)'

    // 12) Create a struct that has an int field. Instantiate a vector of these structs.
    // Instantiate another instance of this struct.
    struct MyStruct{
        int myInt;
    };
    std::vector<MyStruct> myStructVector;
    MyStruct myStruct;
    
    // 13) Call AddToValues2 w/ the vector of structs and single struct from #12
    AddToValues2(myStructVector, myStruct);
    // Is there an error? If yes, what is it?
    //
    // Answer: There is no error that i am aware of. The struct is added to the vector successfully.

    // 14) If there was an error, attempt to fix it.
}
